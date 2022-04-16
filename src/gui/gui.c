#include "gui.h"

#include "../config.h"

#include "../image/image-binarization.h"
#include "../image/image-greyscale.h"
#include "../image/image.h"
#include "../neural-network/network-save.h"
#include "../neural-network/network.h"
#include "../utils/array.h"
#include <stdio.h>
#include <stdlib.h>

char *path_file = NULL;

int network_initialized = 0;

struct Network network;

size_t ans = 0;

GtkWidget *top_level_window;
GtkWidget *result_label;
GtkWidget *image;

GdkPixbuf *tmp_pixbuf;
GdkPixbuf *source_pixbuf;

GError *err = NULL;

int gui_launch(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);

    GtkBuilder *builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "assets/design.glade", &err);

    if (err != NULL)
    {
        fprintf(stderr, "Unable to read file: %s\n", err->message);
        g_error_free(err);
        return 1;
    }

    top_level_window = GTK_WIDGET(gtk_builder_get_object(builder, "top_level_window"));
    g_signal_connect(top_level_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    result_label = GTK_WIDGET(gtk_builder_get_object(builder, "result_label"));
    image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(top_level_window);

    gtk_main();

    network_free(&network);

    return 0;
}

void on_load_neural_network_button_clicked(GtkButton *b)
{
    (void)b;

    if (network_initialized == 0)
    {
        network = network_build(NUM_LAYERS, sizes_layers);
        network_import(&network);
        printf("Network loaded\n");

        network_initialized = 1;
    }
    else
    {
        printf("Network already loaded\n");
    }
}

void on_feedforward_button_clicked(GtkButton *b)
{
    (void)b;

    if (path_file == NULL || network_initialized == 0)
        return;

    struct Image image = image_build(path_file);

    image_greyscale(&image);

    image_binarization(&image);

    double *input = image_build_input(&image);

    image_free(&image);

    double output[OUTPUT_NEURONS] = {0};

    network_feedforward(&network, input, output);

    free(input);

    compute_output(array_max_index_double(output, OUTPUT_NEURONS));
}

void on_file_chooser_button_file_set(GtkFileChooserButton *file_chooser)
{
    path_file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    source_pixbuf = gdk_pixbuf_new_from_file(path_file, &err);
    tmp_pixbuf = gdk_pixbuf_scale_simple(source_pixbuf, 500, 500, GDK_INTERP_NEAREST);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), tmp_pixbuf);
}

void compute_output(size_t output)
{
    char ans[] = "1";
    if (output <= 9)
    {
        ans[0] = output + 48;
    }
    else if (output >= 10 && output <= 35)
    {
        ans[0] = output - 10 + 65;
    }
    else
    {
        ans[0] = output - 36 + 97;
    }

    gtk_label_set_text(GTK_LABEL(result_label), ans);
}