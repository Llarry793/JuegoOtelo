#include "heuristic.h"

float h(Player pl, Board b) {

	if (Name(pl) == "Alice"){
		//Esta heuristica es la mejor
	    const float diskCountWeight = 1.0;
	    const float mobilityWeight = 0.5;
	    const float cornerControlWeight = 2.0;
	    const float edgeControlWeight = 1.0;

	    // Evaluación del recuento de fichas: más fichas es mejor
	    float diskCount = 0.0;

	    // Evaluación de la movilidad: más movimientos disponibles es mejor
	    float mobility = static_cast<float>(b.ValidMoves(pl).size() - b.ValidMoves(Opponent(pl)).size());

	    // Evaluación del control de esquinas: tener más esquinas es beneficioso
	    float cornerControl = 0.0;
	    const Square corners[] = { make_pair('1', 'A'), make_pair('1', 'H'), make_pair('8', 'A'), make_pair('8', 'H') };

	    for (const auto& corner : corners) {
		if (b.Content(corner) == Tk(pl)) {
		    cornerControl += 1.0;
		}
	    }

	    // Evaluación del control de bordes: tener más bordes es beneficioso
	    float edgeControl = 0.0;

	    // Bordes horizontales
	    for (char i = '1'; i <= '8'; i += 7) {
		for (char j = 'B'; j <= 'G'; ++j) {
		    if (b.Content(make_pair(i, j)) == Tk(pl)) {
		        edgeControl += 1.0;
		    }
		}
	    }

	    // Bordes verticales
	    for (char j = 'A'; j <= 'H'; j += 7) {
		for (char i = '2'; i <= '7'; ++i) {
		    if (b.Content(make_pair(i, j)) == Tk(pl)) {
		        edgeControl += 1.0;
		    }
		}
	    }

	    // Puntuación total ponderada
	    float totalScore = diskCountWeight * diskCount +
		               mobilityWeight * mobility +
		               cornerControlWeight * cornerControl +
		               edgeControlWeight * edgeControl;

	    return totalScore;
    }else if (Name(pl) == "Bob"){
    		//Esta heuristica es buena, pero no la mejor
	    const float diskCountWeight = 1.0;
	    const float mobilityWeight = 0.5;
	    const float centralControlWeight = 2.0;
	    const float cornerControlWeight = 2.0;
	    const float edgeControlWeight = 1.0;

	    // Evaluación del recuento de fichas: más fichas es mejor
	    float diskCount = 0.0;

	    for (unsigned i = 0; i < BOARD_SIZE; i++) {
		for (unsigned j = 0; j < BOARD_SIZE; j++) {
		    if (b.Content(make_pair('1' + i, 'A' + j)) == Tk(pl)) {
		        diskCount += 1.0;
		    }
		}
	    }

	    // Evaluación de la movilidad: más movimientos disponibles es mejor
	    float mobility = static_cast<float>(b.ValidMoves(pl).size() - b.ValidMoves(Opponent(pl)).size());

	    // Evaluación del control de casillas centrales: dar más importancia a las casillas centrales
	    float centralControl = 0.0;
	    const Square centralSquares[] = { make_pair('4', 'D'), make_pair('4', 'E'), make_pair('5', 'D'), make_pair('5', 'E') };

	    for (const auto& centralSquare : centralSquares) {
		if (b.Content(centralSquare) == Tk(pl)) {
		    centralControl += 1.0;
		}
	    }

	    // Evaluación del control de esquinas: tener más esquinas es beneficioso
	    float cornerControl = 0.0;
	    const Square corners[] = { make_pair('1', 'A'), make_pair('1', 'H'), make_pair('8', 'A'), make_pair('8', 'H') };

	    for (const auto& corner : corners) {
		if (b.Content(corner) == Tk(pl)) {
		    cornerControl += 1.0;
		}
	    }

	    // Evaluación del control de bordes: tener más bordes es beneficioso
	    float edgeControl = 0.0;

	    // Bordes horizontales
	    for (char i = '2'; i <= '7'; i += 5) {
		for (char j = 'B'; j <= 'G'; ++j) {
		    if (b.Content(make_pair(i, j)) == Tk(pl)) {
		        edgeControl += 1.0;
		    }
		}
	    }

	    // Bordes verticales
	    for (char j = 'B'; j <= 'G'; j += 7) {
		for (char i = '2'; i <= '7'; i++) {
		    if (b.Content(make_pair(i, j)) == Tk(pl)) {
		        edgeControl += 1.0;
		    }
		}
	    }

	    // Puntuación total ponderada
	    float totalScore = diskCountWeight * diskCount +
		               mobilityWeight * mobility +
		               centralControlWeight * centralControl +
		               cornerControlWeight * cornerControl +
		               edgeControlWeight * edgeControl;

	    return totalScore;
    }
    return -1;
}


/*
//Esta heuristica es buena, pero no la mejor
float h(Player pl, Board b) {
    const float diskCountWeight = 1.0;
    const float mobilityWeight = 0.5;
    const float centralControlWeight = 2.0;
    const float cornerControlWeight = 2.0;
    const float edgeControlWeight = 1.0;

    // Evaluación del recuento de fichas: más fichas es mejor
    float diskCount = 0.0;

    for (unsigned i = 0; i < BOARD_SIZE; i++) {
        for (unsigned j = 0; j < BOARD_SIZE; j++) {
            if (b.Content(make_pair('1' + i, 'A' + j)) == Tk(pl)) {
                diskCount += 1.0;
            }
        }
    }

    // Evaluación de la movilidad: más movimientos disponibles es mejor
    float mobility = static_cast<float>(b.ValidMoves(pl).size() - b.ValidMoves(Opponent(pl)).size());

    // Evaluación del control de casillas centrales: dar más importancia a las casillas centrales
    float centralControl = 0.0;
    const Square centralSquares[] = { make_pair('4', 'D'), make_pair('4', 'E'), make_pair('5', 'D'), make_pair('5', 'E') };

    for (const auto& centralSquare : centralSquares) {
        if (b.Content(centralSquare) == Tk(pl)) {
            centralControl += 1.0;
        }
    }

    // Evaluación del control de esquinas: tener más esquinas es beneficioso
    float cornerControl = 0.0;
    const Square corners[] = { make_pair('1', 'A'), make_pair('1', 'H'), make_pair('8', 'A'), make_pair('8', 'H') };

    for (const auto& corner : corners) {
        if (b.Content(corner) == Tk(pl)) {
            cornerControl += 1.0;
        }
    }

    // Evaluación del control de bordes: tener más bordes es beneficioso
    float edgeControl = 0.0;

    // Bordes horizontales
    for (char i = '1'; i <= '8'; i += 7) {
        for (char j = 'B'; j <= 'G'; ++j) {
            if (b.Content(make_pair(i, j)) == Tk(pl)) {
                edgeControl += 1.0;
            }
        }
    }

    // Bordes verticales
    for (char j = 'A'; j <= 'H'; j += 7) {
        for (char i = '2'; i <= '7'; ++i) {
            if (b.Content(make_pair(i, j)) == Tk(pl)) {
                edgeControl += 1.0;
            }
        }
    }

    // Puntuación total ponderada
    float totalScore = diskCountWeight * diskCount +
                       mobilityWeight * mobility +
                       centralControlWeight * centralControl +
                       cornerControlWeight * cornerControl +
                       edgeControlWeight * edgeControl;

    return totalScore;
}
*/

