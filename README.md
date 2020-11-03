# MathGame
A puzzle and math game for Arduboy.
I want to make this project public to give developers insight on game development.
Game design documents, commented code. How a person who went to school & has professional experience does it?

The only thing I'm not going to share directly is my JIRA database. I'll do some kind of analysis instead with pictures.

## Play now!

The latest version available on Github can be played by using the following link: https://felipemanga.github.io/ProjectABE/?url=https://github.com/HokuHakase/MathGame/raw/master/bin/mathGame.ino.hex

## NEEDED TOOLS
The tools below are what I'm using. Feel free to use your own setup but I may not be able to help you.

- Visual Studio Code
- Arduino Extension for VSC
- Arduino IDE (For the above extension to work)
- OpenOffice
- CF+ Extension for OpenOffice (https://extensions.openoffice.org/en/project/extend-your-conditional-formatting)

## Game Design Teardown
The GDT is the document that lists what are the expected features for the game. One line represents one statement.

Each statement has a priority, which can be:
- "Must Have", this line is a vital component for the game to work.
- "Should Have", this line adds polish to the game. More often than not visual polish.
- "Nice to Have", a feature that the game can live without. Can be a new feature altogether or more polish.

Each statement has a state, which can be:
- "Not Started", nobody worked on this statement at all.
- "In Progress", this statement is under active development.
- "In Review", this statement is being verified by another team member. This line is optional based on the project type.
- "Integrated", this statement is done. Only bug fixes should happen.
- "Cut", this statement is no longer relevant to the scope of the project. No development should be done on it.

Each statement has a QA status, which can be:
- "Not Implemented", this statement is not in the game.
- "Not Okay", this statement has a major issue that prevents its function.
- "Okay But", this statement has a minor issue but still works.
- "Okay", this statement has no issue and fully works.

If the QA Status is anything but "Not Implemented" or "Okay", there should be a Bug ID or a note next to it.

