-----------------------------------------------------------Video Link
Playthrough video: https://youtu.be/r3bEpLPFdek.

-----------------------------------------------------------Brief code-flow explanation
Code runthrough. The play() method contains the main game loop. First, play calls intializeGame to create the rooms, items, and player, and
to link the rooms to eachother and put items in the rooms. Next, play enters a loop which does not end until the player escapes the dungeon.
The loop asks for user input, then executes code based on the input. go DIRECTION will take the user in the direction if they are allowed
to do so. the same goes for take ITEM, use ITEM, and drop ITEM. The user is prompted to type 'help me' if they need to be reminded of the
instructions on every loop. The user can use the look command to see the room, any items in the room, the directions he/she can try to travel 
in, and to be reminded of what's in their inventory.

------------------------------------------------Game requirements and how they are implemented
Your game must have at least 8 rooms.
>Check initializeGame().

Your game must allow rooms to contain items.
>Check initializeGame(). Items are adde using addItem which takes the head node of the room and the item to be added as parameters.

Your game must implement an avatar where the avatar has an inventory (a place to put items).
>Check top of adventure.c and initializeGame(). Items are added to avatar's inventory using addItem in the game loop 'take ITEM' logic.
 
Your game must allow an avatar to “see” the room they are in with the command “look”.
>This is implemented in look() which calls several print functions including roomToString, printItems, 

Your game must allow an avatar to move through each room using the command “go DIRECTION” where DIRECTION is a direction: north, south, east, west, up, down.
>This is implemented in the play loop. Rooms are connected in initializeGame.

Your game must allow an avatar to pick up items with the command “take ITEM” where ITEM is the name of an item in a room.
>This is implemented in the play loop under the case 'take ITEM'.

Your game must allow an avatar to use an item with the command “use ITEM” where ITEM is the name of an item in the avatars inventory. The effect of using an item depends on the room the avatar is in.
>See explanation for the next requirement.

You must implement at least one instance where an item alters the state of a room that the avatar is in.
>There are four instances. Each room has a 'requirement' field which will disqualify a go DIRECTION command into the room 
unless the requirement field is NULL. The logical interaction between item and room is contained in the play loop under the case 'use ITEM'
and is well-documented.

Your game must allow an avatar to drop an item with the command “drop ITEM” where ITEM is the name of an item in the avatars inventory.
>Check this logic in the bottom of the game loop in play(). Item is removed from player's inventory using item_take and added to room's items list
using addItem.

Your game must have a winning state (allowing the game to end).
>Check gameIsOver() and its use in the main game loop in play().

------------------------------------------------Code requirements and how they are implemented

You must use C structs in your code to represent various game objects.
>See structs for avatar, room, item.

You must use pointers in your code.
>Rooms, Items, and more are referenced by pointers only, after construction.

You must use dynamic allocation in your code using malloc/calloc.
>Rooms, Items, Avatars are instantiated using malloc.

You must deallocate memory in your code using free.
>See deinitializeGame() and the functions freeRooms and freeItems.
