# Custom Text Renderer for Game Editor

An alternative way to render text in [Game Editor](http://www.game-editor.com).

This text renderer doesn't use Game Editor's built-in text actors at all, but instead, uses normal actors for displaying the text. Every character is a unique clone.

The system requires the fonts to be in an image format. For creating the font images and configuring the font settings (letter spacing, word spacing, line spacing and indentation) use the Font Tool that is provided together with the system.

## Features

* Automatic text alignment (left / center / right)
* Automatic line wrapping (allows fitting text in an area of a given width)
* Custom color coding (allows rendering text in multiple colors)
* Fitting text in an area of a given size (allows fitting large paragraphs of text in small windows by using scrollable text)
* Optimized performance (text is only updated on request)

A video demonstrating some of the features listed above can be found on [YouTube](https://www.youtube.com/watch?v=g_q5VWQEdx4).
