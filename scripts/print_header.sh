#!/bin/bash
for i in {0..2} ; do
    for color in {0..214} ; do # Colors
        # Display the color
		clear
        printf "\e[38;5;%sm" $color
		echo "###############################################################"
		echo "#                                                             #"
		echo "#      CCCCCCC    .     .     BBBBBB            .DDDDDDD      #"
		echo "#    / ______/   /U     U\\   B  __   \\  333333  D \\    / \\    #"
		echo "#   C C         U U     U U  B B__B  /       3  D  DDDD   D   #"
		echo "#   C C         U U     U U  B--__--B    33333  D  D  D   D   #"
		echo "#   C C-------  U U_____U U  B B__B  \\       3  D  DDDD   D   #"
		echo "#   CCCCCCCCC/  U         U  B      /   333333  D        /    #"
		echo "#                \\UUUUUUU/    BBBBBB              DDDDDD      #"
		printf "#                                     \e[36;1mGlaurent\e[38;5;%sm                #\n" $color
		echo "#                                                             #"
		echo "###############################################################"
		echo
        # Display 6 colors per lines and clear
    done
done
exit 0
