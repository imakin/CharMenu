CharMenu
========

Easy menu drawer to use with 16x2 character LCD for AVR. 
It uses lcd_lib.h from Scienceprog.com (GPL license)

example usage on my friend's repository https://github.com/firdanas/tombol
=======
CharMenu
========

Easy menu drawer to use with 16x2 character LCD for AVR. 
This CharMenu uses lcd_lib.h from Scienceprog.com (GPL license). We all know that embedded system firmwares were built statically linked to any library it uses, thus the same license is being used for this CharMenu.

What is this?
========

16x2 Char LCD is popular among embedded system, widely used in system debugging even for user display. 
Building menu and its navigation for this limited characters LCD with good __User-Experience__ is a bit hard. Therefore CharMenu propose the use of four buttons: ```[Enter]``` ```[Back]``` ```[Scroll Left]``` ```[Scroll Right]``` to navigate through the options displayed in the LCD. 

![what is it](https://cloud.githubusercontent.com/assets/6647566/5604155/a92d7be8-93dc-11e4-8a39-7c6a2ce198cf.jpg)

The two scroll button will navigate the menu to the left/right which is sibling menu.
Enter button will either enter the submenu (children menu) or execute some callback function to do.
Back button will navigate the menu to the parent's menu

For an example, there are these menu:
```
                            [MainMenu]
              [FoodMenu]------------------[DrinkMenu]
          [Pizza]---[Kebab]     [CocaCola]--[Pepsi]--[BigCola]
```
Inside the MainMenu there are two menus, to pick Food or Drink. Inside FoodMenu there are menus to pick wether to run pizza or kebab. On the image above, the ```Kebab``` menu is displayed, thus the cursor is to navigate between ```Kebab``` and ```Pizza```. Hitting Enter will execute the function callback which is binded to the ```kebab``` menu. Hitting prev/scroll left button will navigate the menu to ```Pizza``` menu, Hitting next/scroll right menu will get the cursor to the next menu which --as ```kebab``` is already the right most menu-- will jump the cursor to the left most menu: ```Pizza```. Back button will return the menu to its parent menu, the menu to pick either ```FoodMenu``` or ```DrinkMenu```.

Usage
========
See example
