# Group Name HERE!

# Members
Eduardo Lozano, Aiden Mizhen, Paul Serbanescu
# A statement of the problem you are solving and/or a high level description of the project.
We aim to create a multiplayer game hosted on a server. We want the game to work with any (reasonable) amount of users.
# A description as to how the project will be used (describe the user interface).
Players will be able to connect to the server and play a simple text based game (we haven't decided what game yet) and send messages.
# A description of your technical design. This should include:
## How you will be using the topics covered in class in the project.
We will use Pipe Networking, Sockets, Forking, and (normal) Piping to create a forking server which can communicate to the main server running the game.
## How you are breaking down the project and who is responsible for which parts.
* We will first create the forking server and use sockets to allow incoming requests
* Next we will create the communication between the main server and all of the children to send messages to a public chat and display a common UI to all those who connected to the server
* Finally we will make some kind of text based game and expand toon it depending on how much time we have left
## What data structures you will be using and how.
     
## What algorithms and /or data structures you will be using, and how.
    
# A timeline with expected completion dates of parts of the project.
