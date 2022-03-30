CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD
OBJECTS = main.o piece.o cell.o board.o player.o game.o gamedisplay.o king.o pawn.o knight.o bishop.o rook.o queen.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm $ ${OBJECTS} ${EXEC} ${DEPENDS}

