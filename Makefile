# -Wall -Werror -Wextra -pedantic
build:
	gcc  ./src/*.c -Iinc -lm -lSDL2 -lSDL2_image -o maze;

# run:
# 	./maze maps/map_I.txt;
