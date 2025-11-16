#include "alphabeta.h"
#include "heuristic.h"



/*
float Minimax(Player pl,Board b,unsigned depth,bool maximizingPlayer,Move &best_move)

Parameters:
Player pl:             the player who is about to put a token

Board b:               the current state of the board

unsigned depth:        the current depth. In the first call it should be passed as the chosen
                       depth. In further recursive calls it is diminished so when it arrives to 0
                       it plays the role of a signal to warn us of not going on searching.

bool maximizingPlayer: boolean variable to indicate if this is the player who wants to
                       maximize or to minimize. When a player calls Minimax to choose his/her
                       move, it should be passed as true (he/she is trying to get the maximum
                       value of the function) but when Minimax is recursively called, it should
                       be passed as false if we have come here with true (since a minimization
                       step follows a maximization one) and conversely. See the actual code.

Move &best_move:       Variable to return the best move we have found at this level. The best move
                       for deeper levels is found, too, but not returned, since we are only interested
                       in what to do from here, not in the prospective decisions we think our opponent
                       will take (even such decisions have lead us to arrive to our final decision).
                       Again, see actual code. 
                       
float alpha:		--escribir aqui la funcion que realiza--

float beta:		--escribir aqui la funcion que realiza--

Returns:
			The optimal value of the evaluation function
*/

float AlphaBeta(Player pl,Board b,unsigned depth,bool maximizingPlayer,Move &best_move, float alpha, float beta)
{
	 Sqlist sons=b.ValidMoves(pl);		//Crea una lista de casillas (sons) con los movimientos posibles a partir de las casillas en las que al jugador dado (pl) se le permite poner ficha
	 
	 if ( depth==0 || sons.empty() )	//Si se alcanza la profundidad maxima (depth==0) o no hay mas movimientos disponibles (sons.empty())
	  return h(pl,b);			//Se evalua la funcion heuristica y se devuelve el valor de ésta

	 float best_value;
	 
	 if (maximizingPlayer)			//Si el jugador es maximizante (nodo maximizante)
	 {

		  best_value=-FLT_MAX;		//se inicializa a menos infinito para posteriormente ser actualizado

		  float v;
		  Move mv;

		  for (Sqlist::iterator it=sons.begin();it!=sons.end();it++)	//Se recorren todos los movimientos posibles 
		  {
			   mv=make_pair(pl,(*it));				//Se "emparejan" para formar un movimiento (cada movimiento se compone de jugador y casilla)

			   bool legal=false;
			   Board child=b.TryMove(mv,legal);			//Se crea una copia del tablero con cada movimiento posible para simularlo
			   
			   if (!legal)
			   {
				    cerr << "Error from AlphaBeta: trying illegal movement.\n";
				    exit(1);
			   }
			   
			   Move dummy_move;						//Crea una variable de tipo movimiento que no va a tener ningún uso 
			   v=AlphaBeta(Opponent(pl),child,depth-1,false,dummy_move, alpha, beta);	//Realiza la llamada recursiva a AlphaBeta para el oponente(Opponent(pl)), 
			   								//se disminuye la profundidad(depth-1),
			   								//se pasa como tablero el del movimiento simulado (child) (linea 61)
			   								//y se cambia eltipo de jugador de maximizante a minimizante (o viceversa)(false)
			   
			   if (v>best_value)		//Si se encuentra un valor mejor
			   {
				    best_value=v;	//se actualiza el mejor valor
				    best_move=mv;	//se actualiza el mejor movimiento
			   }
			   
			   /*
			   	La variable alpha representa el valor actual más alto que el jugador maximizador puede garantizar, 
			   	y se actualiza con el valor más alto encontrado hasta el momento durante la búsqueda del árbol.
			   */
			   if(alpha < v)	//Se realiza la poda de alfa
			   	alpha = v;	//Se actualiza el valor de alfa
			   	
			   /*
			   	Si se detecta que beta (el valor que el oponente minimizador puede garantizar) es menor o igual que alpha, se produce una poda alfa-beta. 
			   	En este caso, se detiene la exploración adicional del árbol de juego ya que el valor alpha (el mejor valor para el jugador maximizador) 
			   	es lo suficientemente alto como para asegurar que el oponente minimizador no elegirá este camino, porque ya tiene al menos una opción igual o mejor, 
			   	lo que hace que la rama actual no sea de interés para la toma de decisiones final.
			   */
			   if(beta <= alpha)
			   	return best_value;
		  }
		  return best_value;
	 }
	 else		//Si el jugador es minimizante (nodo minimizante)
	 {
		  best_value=FLT_MAX;		//Se inicializa a infinito el valor para posteriormente ser actualizado
		  float v;
		  Move mv;
		  
		  for (Sqlist::iterator it=sons.begin();it!=sons.end();it++)	//Se recorren todos los movimientos posibles 
		  {
			   mv=make_pair(pl,(*it));				//Se crea un par que representa un movimiento (jugador y posicion)
			   bool legal=false;
			   Board child=b.TryMove(mv,legal);			//Se intenta realizar el movimiento actual en un tablero copia
			   
			   if (!legal)
			   {
				    cerr << "Error from AlphaBeta: trying illegal movement.\n";
				    exit(1);
			   }
			   // The only change here is that, since we were minimizing players, our opponent
			   // was a maximizing one, hence the 'true'.
			   
			   Move dummy_move;						//Crea una variable de tipo movimiento que no va a tener ningún uso
			   v=AlphaBeta(Opponent(pl),child,depth-1,true,dummy_move, alpha, beta);
			   // Another difference: v is kept if it is _smaller_ (not larger) than the value up to now.
			   
			   if (v<best_value)
			   {
				    best_value=v;
				    best_move=mv;
			   }
			   if(beta > v)
			   	beta = v;
			   if(beta <= alpha)
			   	return best_value;
		  }
		  return best_value;
	 }
}  


