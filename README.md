# Group Name HERE!

# Members
Eduardo Lozano, Aiden Mizhen, Paul Serbanescu
# A statement of the problem you are solving and/or a high level description of the project.
We aim to create a multiplayer chat hosted on a server. We want the chat to work with any (reasonable) amount of users.
The server will list all ongoing matches as well as lobbies waiting for players to join. A user will be able join any lobby as a player or spectator
# A description as to how the project will be used (describe the user interface).
Players will be able to connect to the server and either:
- Create a match and wait for sufficient players to join
- Join a match
- Spectate an ongoing match
- Send chat messages during a match (playing or spectating)
# A description of your technical design. This should include:
## How you will be using the topics covered in class in the project.
We will use Pipe Networking, Sockets, Forking, and (normal) Piping to create a forking server which can communicate to the main server running the chat.
## How you are breaking down the project and who is responsible for which parts.
* We will first create the forking server and use sockets to allow incoming requests
* Next we will create the communication between the main server and all of the children to send messages to a public chat and display a common UI to all those who connected to the server
* Finally we will make some kind of text based chat and expand toon it depending on how much time we have left
## What data structures you will be using and how.
We will be using structs for messages / message history OR we will be using a file as a buffer to write all the messages.
## What algorithms and /or data structures you will be using, and how.
Not any algorithms in particular but perhaps recursion to get nested bolded / italics to work. 
# A timeline with expected completion dates of parts of the project.
finish before deadline
