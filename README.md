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

## Getting started

To use the system, just download the repository as a .zip by clicking the green "Clone or download" button and selecting "Download ZIP". Extract the contents of the .zip and merge the CTR_template.ged to your game. You may need to make sure that there is no name collisions between your game and the template, as the actors, variables and functions of the template are not prefixed in any way yet.

A more comprehensive usage guide will be available later.

## Supported escape sequences

- **\n** - normal line break, if automatic line wrapping is in use, this may be ignored
- **\v** - forced line break (actually stands for vertical tab, but has been repurposed here)
- **\t** - tabulation

## Custom escape sequences

The system also includes some custom escape sequences. All these sequences start with '$'.

- **$$** - prints a single '$'
- **$_** - a non-breaking space, is not allowed to be replaced with a newline for line wrapping
- **$c000000** - deploys color override: all following text will be rendered using the specified color
    - Each pair of characters after c represents a hexadecimal value between 0-255, first pair is for red, second for green, last one for blue
    - Example: $c00ffff is interpreted as (0, 255, 255) i.e. cyan
- **$x** - a finishing escape sequence, the character after x determines what effect is to be finished
    - $xc - stops color override: all following text will be rendered using the normal color of the text in question
