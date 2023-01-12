## Day 0
Paul, Eduardo, & Aiden:
Populate project proposal

## 01/09/23
* Agreed on and designed system architecture
* We drew a diagram/flowchart to show the path of communication
* We have data that is shared among all clients (The chat or game board) and data that is specific to the client (game stats)
* Client-specific data is processed and created in the client specific sub-server
* Shared data is processed in the main server and distributed to the sub servers
* Clients only talk to sub-servers who mediate between them and the main server

## 01/10/23
* Decided to remove the middle men and just use select
* Changed plan for the project, and setup boilerplate code
* Designed user interface; will use terminal formatting. Page will refresh whenever a new message is sent

## 01/11/23
* Created data structures for a message and a linked list for a queue for storing message history
