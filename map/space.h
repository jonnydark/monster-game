/*
 * space.h
 *
 * This contains the class declaration for spaces 
 * Spaces are the basic building blocks of the map. Each place on the map is a 
 * space object. There are to be three types of spaces, normal, items and pitfalls.
 * 
 * The character 'out' contains a representational character for the map to print. By
 * default this is a blank space. When the player is on the space - it becomes O. 
 * It is also possible for the player to set a marker on a particular space making
 * it become "!"
 *
 * Normal Spaces - Do very little at all and just serve as stepping stones
 *
 * Item spaces - These are where you will find items. After an item is picked up, 
 * item spaces become normal spaces
 *
 * Pitfalls - If the player lands on a pitfall space - it's game over. There will be a
 * system that warns players of pitfalls in their vicinity
 *
 *
 * space type key
 *  0 - normal
 *  1 - pitfall
 *  2 - item
 */

#ifndef SPACE_H
#define SPACE_H

// Forward declare the iostream
#include <iosfwd>


namespace dungeon_map 
{
  enum SpaceType { NormalSpace, Pitfall, ItemSpace };

  class space 
  {
    protected:
      SpaceType type;
      int itemID; 
      char out; // contains the char that is returned for map output, ' ', O, or !
      bool marked; 

    public:
      // constructor = needs to assign type and item if needed
      space(): type(NormalSpace), out(' '), marked(false) {}

      // destructor - might not need to do anything
      virtual ~space() {}

      // Sets the value of the map icon
      void set(char x) {
        out = x;
      }

      // Function returns true if marker is set
      bool isMarked() const {
        return marked;
      }

      // Function to set a marker
      void mark();

      //Function to remove a marker
      void unmark();
   
      //Returns the type of space this is
      SpaceType getType() const {
        return type;
      }

      // Used to set the type of the spaces. Only accepts 0 or 1
      // Use setItemID() to convert space to item space
      void setType(SpaceType newType);
     
      /*
       * All the items have a unique ID. The item ID can be passed
       * to a function in the player class to instantiate the item
       * in the player's inventory
       */
      // Sets space to type 2 (item space) and sets the itemID
      void setItemID(unsigned int ID) {
        type = ItemSpace;
        itemID = ID;
      }

      // itemID accessor
      int getItemID() const {
        return itemID;
      }

      // overload insertion operator - returns the value of out
      friend std::ostream & operator<<(std::ostream &oss, const space &sp);

  };

}

#endif
