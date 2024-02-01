use fltk::{prelude::*, *};
use fltk::button::Button;
use fltk::frame::Frame;
use fltk::group::Flex;
use fltk::input::Input;
use fltk::window::Window;
use tokio::time::{sleep, Duration};

#[tokio::main]
async fn main() {

    let a = app::App::default().with_scheme(app::Scheme::Gtk);
    let mut win = window::Window::default().with_size(640, 480);
    let mut col = group::Flex::default_fill().column();
    frame::Frame::default();

    let mut mp = group::Flex::default().row();
    frame::Frame::default();
    let spacer = frame::Frame::default();


    let mut bp = group::Flex::default().column();
    frame::Frame::default();
    let w = frame::Frame::default().with_label("Distributed System");


    let mut urow = group::Flex::default().row();
    frame::Frame::default().with_label("Username:").with_align(enums::Align::Inside | enums::Align::Right);
    let mut username = input::Input::default();
    let mut current_user = String::new();

    urow.fixed(&username, 180);
    urow.end();

    let pad = frame::Frame::default();
    let mut mainwindow =win.clone();
    let mut brow = group::Flex::default().row();

    frame::Frame::default();
    let mut login = create_button("Login");
    brow.fixed(&login, 80);
    brow.end();

    let mut hidden_text = Input::default()
        .with_pos(10, 50)
        .with_size(380, 30);
    hidden_text.set_color(enums::Color::Red);
    hidden_text.set_text_color(enums::Color::White);
    hidden_text.set_frame(enums::FrameType::FlatBox);
    hidden_text.hide();

    login.set_callback(move |_| {
        current_user= username.value();

        if  current_user==""{
            println!("User already connected to the server");
            hidden_text.show(); // Show the hidden text box
            hidden_text.set_value("User is already connected to the server"); // Set the text value

        }
        else{
            mainwindow.hide();
            println!("Logged in as: {}", current_user);

            let mut win = Window::default().with_size(640, 480);
            // Create the main layout (left and right panels)
            let mut col = Flex::default_fill().row();

            // Create the left panel with buttons
            let mut left_panel = Flex::default_fill().column();
            let mut new_chat_button = create_button("New Chat");
            left_panel.add(&new_chat_button);
            col.add(&left_panel);

            // Create the right panel with a textbox for user input
            let mut right_panel = Flex::default_fill().column();
            let mut input_frame = Frame::new(0, 0, 150, 30, "");
            let mut user_input = Input::new(0, 0, 150, 30, "");
            let mut submit_input_button = Button::new(0, 0, 150, 30, "Submit");

            right_panel.end();
            right_panel.add(&input_frame);
            right_panel.add(&user_input);
            right_panel.add(&submit_input_button);

            col.add(&right_panel);

            // Set up window properties
            win.resizable(&col);
            win.set_color(enums::Color::from_rgb(250, 250, 250));
            win.end();
            win.show();
            win.size_range(600, 400, 0, 0);

            submit_input_button.set_callback(move |_| {
                let input_text = user_input.value();
                // Do something with the user input, for example, print it
                println!("Message: {}", input_text);
                user_input.set_value("");
            });

            let mut in_frame= input_frame.clone();
            // Set up the callback for the "New Chat" button
            new_chat_button.set_callback(move |_| {
                // Prompt the user to enter the receiver's name and IP address using input fields
                let mut wind = window::Window::new(100, 100, 600, 300, "Receiver Information");
                let mut receiver_name_input = input::Input::new(120, 10, 300, 30, "Receiver Name:");
                let mut submit_button = button::Button::new(420, 10, 70, 70, "Submit");
                let mut panel= left_panel.clone();

                let mut hidden_text = Input::default()
                    .with_pos(10, 50)
                    .with_size(380, 30);
                hidden_text.set_color(enums::Color::Red);
                hidden_text.set_text_color(enums::Color::White);
                hidden_text.set_frame(enums::FrameType::FlatBox);
                hidden_text.hide();

                wind.end();
                wind.show();

                let mut in_frame= in_frame.clone();
                submit_button.set_callback(move |_| {
                    // Declare variables to store user input
                    let mut receiver_name_storage = String::new();
                    let receiver_name = receiver_name_input.value();
                    receiver_name_storage = receiver_name.to_string();

                    if receiver_name_storage=="" {
                        println!("User does not exist");
                        hidden_text.show(); // Show the hidden text box
                        hidden_text.set_value("User does not exist"); // Set the text value
                    }
                    else{
                        let mut new_user_button = create_button(&receiver_name_storage);
                        panel.add(&new_user_button);
                        wind.hide();

                        let mut in_frame= in_frame.clone();
                        new_user_button.set_callback(move |_| {
                            in_frame.set_label(&receiver_name_storage);
                            println!("Sending message to: {}", receiver_name_storage);
                        });
                    }
                });

            });
        }
    });


    let b = frame::Frame::default();

    frame::Frame::default();

    bp.fixed(&w, 60);
    bp.fixed(&urow, 30);
    bp.fixed(&pad, 1);
    bp.fixed(&brow, 30);
    bp.fixed(&b, 30);
    bp.end();

    frame::Frame::default();
    mp.fixed(&spacer, 10);
    mp.fixed(&bp, 300);
    mp.end();

    frame::Frame::default();
    col.fixed(&mp, 200);
    col.end();

    win.resizable(&col);
    win.set_color(enums::Color::from_rgb(250, 250, 250));
    win.end();
    win.show();
    win.size_range(600, 400, 0, 0);
    a.run().unwrap();
}

fn create_button(caption: &str) -> button::Button {
    let mut btn = button::Button::default().with_label(caption);
    btn.set_color(enums::Color::from_rgb(225, 225, 225));
    btn
}

