#include <gtk/gtk.h>

static GtkCssProvider *cssProvider;
static GtkWidget *button;
static GtkWidget *button2;

static void On_click_button(GtkWidget *widget,
                            gpointer data)
{
    g_print("botton 1\n");
    gtk_css_provider_load_from_path(cssProvider, "style2.css");

    gtk_style_context_add_provider_for_display(
        gtk_widget_get_display(widget),
        GTK_STYLE_PROVIDER(cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}
static void On_click_button2(GtkWidget *widget,
                             gpointer data)
{
    g_print("botton 2\n");
    gtk_css_provider_load_from_path(cssProvider, "style.css");

    gtk_style_context_add_provider_for_display(
        gtk_widget_get_display(widget),
        GTK_STYLE_PROVIDER(cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
}

static void activate(GtkApplication *app,
                     gpointer user_data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_widget_set_name(window, "window");
    GtkWidget *box;

    // GtkWidget *texto = gtk_label_new("Esto es un label");
    // GtkWidget *texto2 = gtk_label_new("Esto es un segundo label");

    button = gtk_button_new_with_label("Botón 1");
    gtk_widget_set_name(button, "button1");

    button2 = gtk_button_new_with_label("Botón 2");
    gtk_widget_set_name(button2, "button2");

    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);
    gtk_window_set_title(GTK_WINDOW(window), "Hola Mundo");
    // gtk_window_maximize(GTK_WINDOW(window));

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    gtk_box_append(GTK_BOX(box), button);
    gtk_box_append(GTK_BOX(box), button2);
    gtk_box_set_homogeneous(GTK_BOX(box), true);

    g_signal_connect(button, "clicked", G_CALLBACK(On_click_button), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(On_click_button2), NULL);

    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    cssProvider = gtk_css_provider_new();
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}