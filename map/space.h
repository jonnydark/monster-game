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
      space(): type(NormalSpace), out(' '), marked(false) {}

      virtual ~space() {}

      void set(char x) { out = x; }

      bool isMarked() const { return marked; }
      void mark();
      void unmark();
      SpaceType getType() const { return type; }

      bool IsNormalSpace() { return (type == NormalSpace); }
      bool IsItemSpace() { return (type == ItemSpace); }
      bool IsPitfall() { return (type == Pitfall); }

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
