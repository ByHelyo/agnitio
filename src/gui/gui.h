#ifndef AGNITIO_GUI_H
#define AGNITIO_GUI_H

#include <gtk-3.0/gtk/gtk.h>

#include "../neural-network/network.h"

/**
 * launch gui
 *
 * @param argc
 * @param argv
 * @return
 */
int gui_launch(int argc, char **argv);

/**
 * ''load_neural_network'' button clicked
 *
 * @param config
 */
void on_load_neural_network_button_clicked(GtkButton *b);

/**
 * ''on_feedforward'' button clicked
 *
 * @param b
 */
void on_feedforward_button_clicked(GtkButton *b);

/**
 * ''on_file_chooser'' button clicked
 *
 * @param file_chooser
 */
void on_file_chooser_button_file_set(GtkFileChooserButton *file_chooser);

/**
 * get response from network
 *
 * @param output
 */
void compute_output(size_t output);

#endif // AGNITIO_GUI_H
