#include "minimax.h"
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

Returns:
			The optimal value of the evaluation function
*/

float Minimax(Player pl,Board b,unsigned depth,bool maximizingPlayer,Move &best_move)
{
 // First, we get the list of children nodes (possible movements we can do) from here.
 // This will be needed, independently of if we are a minimizing or a maximizing player,
 // and doing now allows us to check a special case: that in which we haven't arrived to the
 // deepest level, but we can't go on (there is NO deeper level!). In such a case, we will
 // do the same as for the base recursive case: return the h-function of this node.
 
 Sqlist sons=b.ValidMoves(pl);
 
 // Base case of the recursion: we have arrived to the deepest level we wanted to arrive,
 // or we can't go deeper.
 // In that case we simply return the value of the heuristic function for the current node.

 if ( depth==0 || sons.empty() )
  return h(pl,b);

 float best_value;
 // First, the case in which the player pl is the same that called this function from
 // the upper level, i.e.: the player that wants to maximize the function:
 if (maximizingPlayer)
 {
  // The best value of all its children. Initialized to -Infinity. To be updated.
  best_value=-FLT_MAX;

  float v;
  Move mv;
  // For each of the possible children nodes (moves): 
  for (Sqlist::iterator it=sons.begin();it!=sons.end();it++)
  {
   // ... build the corresponding move (with pl as player and this square as place)
   mv=make_pair(pl,(*it));

   // Check (for security) that this is a legal move, and if it is, 
   // it returns a new board (a copy) with the state in which the board would be after the move.
   // Notice: we do NOT change the actual board, we work on a copy. Only the main program will 
   // efectively make the move.
   bool legal=false;
   Board child=b.TryMove(mv,legal);
   if (!legal)
   {
    // ValidMoves generates only legal movements, so we should never be here...
    cerr << "Error from Minimax: trying illegal movement.\n";
    exit(1);
   }
   // From that child we call Minimax again with some differences:
   // - This time, the player is the opponent
   // - The depth is reduced (remember: depth 0 signals the deepest level we want to arrive)
   // - Since we were a maximizing player, our opponent is a minimizing one (hence, the 'false')
   // - We are not really interested in the move our opponent would do to face ours; the only
   //   thing we know is it will be his/her best, and we will have taken that into account. But the
   //   the function _needs_ a last parameter, so we pass it a dummy move that will not be used later. 
   Move dummy_move;
   v=Minimax(Opponent(pl),child,depth-1,false,dummy_move);
   // Finally, check is this child is better than the best up to now (better here means bigger), and if so, keep it.
   // The bast value will be returned. The best move will be returned, too, via the referenced variable best_move.
   if (v>best_value)
   {
    best_value=v;
    best_move=mv;
   }
  }
  return best_value;
 }
 // Second alternative: we are the minimizing player
 // Comments would be analogous. We signal only the differences:
 else
 {
  // This time best_value is initialized to +Infinity
  best_value=FLT_MAX;
  float v;
  Move mv;
  for (Sqlist::iterator it=sons.begin();it!=sons.end();it++)
  {
   mv=make_pair(pl,(*it));
   bool legal=false;
   Board child=b.TryMove(mv,legal);
   if (!legal)
   {
    cerr << "Error from Minimax: trying illegal movement.\n";
    exit(1);
   }
   // The only change here is that, since we were minimizing players, our opponent
   // was a maximizing one, hence the 'true'.
   Move dummy_move;
   v=Minimax(Opponent(pl),child,depth-1,true,dummy_move);
   // Another difference: v is kept if it is _smaller_ (not larger) than the value up to now.
   if (v<best_value)
   {
    best_value=v;
    best_move=mv;
   }
  }
  return best_value;
 }
}  


