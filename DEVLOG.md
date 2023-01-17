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

## 01/12/23
* Finished the message linked list.
* Expanded message datatype to include metadata such as user and time sent
* In class we fixed our previously working demo in the server to the sample server code with refresh. Since that is working all we have left is to implement the struct code for message history
* Struct almost fully done

## 01/13/23
* Worked on both forking and selecting server since we had trouble with both. At this moment, not sure which one may work (at all, not just better)

Additionally: worked on the implementation of the server select with old forking version of the code (discontinued as of 1/16)

## 01/15/23
* Made progress on forking server - ran into issue with other's messages only being sent back when the client sent a message
* Ran into issues on splitting server, only one message sent or received at a time.
    *select on the server-end was not the behavior we were looking for

## 01/16/23
* Made progress on selecting server, but got stuck on sending messages back to clients
* Figured out forking server, solved issues with messages, gave up on selecting
* Used terminal escape characters to prevent overwriting
    * Basically made the chat feel more like a chat (less ugly)
* Created usernames
* Created string formatting with terminal escape characters
* Was unable to reset the formatting after printing the escape characters
