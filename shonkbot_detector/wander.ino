
// Wander - cruise about, turning when an object is detected ahead of us

#define STATE_CRUISING 0
#define STATE_TURNING 1

#define BOT_DISTANCE 25
#define COLLISION_DISTANCE 5
#define BOT_ERROR 5

#define LEFT 0
#define RIGHT 1

int state = STATE_CRUISING;
int last_bot_value = 0;
int currentStepper;
int currentTurn = 90;

long clearSteps = -1;

void setupWander()
{
  randomSeed(analogRead(1));
  currentStepper = LEFT;
}


void loopWander()
{

 int range = collisionDetector.getRangeInCm();
 int range_bot = swarmDetector.getRangeInCm();

 Serial.print( "STATE IS " );
 Serial.println( state );

  switch( state )
  { 
    case STATE_CRUISING:
      Serial.print( " range_bot " );
      Serial.println( range_bot );

      if( range_bot > 0 && range_bot < BOT_DISTANCE ) //found another bot 
      {
         Serial.println( " swarm !" );
 
         Serial.println( " found bot with range " );
         Serial.println( range_bot );
         
         if(abs(last_bot_value - range_bot) < BOT_ERROR) // not too much error
         {
          Serial.print( "swarming with error:  " );
          Serial.println( abs(last_bot_value - range_bot) );
          go();
         }       
         else{
          Serial.print( " error too large - turning randomly" );
          Serial.println( abs(last_bot_value - range_bot) );
          Serial.println( " following -> turning " );
          state = STATE_TURNING;
          turnRandom(3,6);
          clearSteps = -1;
         }

         last_bot_value = range_bot;        
        
      }else{

        if( range != 0 ) 
        {
         Serial.println( " cruising -> turning " );
         state = STATE_TURNING;
         clearSteps = -1;
        }
        else
        {
          go();
        }
      }

      break;
      
   case STATE_TURNING:

       if (range == 0 || range_bot == 0 )
       {
         if(currentStepper == LEFT)
         {
           if( leftStepper.currentPosition() > clearSteps )
           {  
             // turn is finished
             currentTurn = 90;
             state = STATE_CRUISING;
           }
           else
           {
             turnLeft();
           }
         }else{

           if( abs(rightStepper.currentPosition()) > clearSteps )
           {  
             // turn is finished
             currentTurn = 90;
             state = STATE_CRUISING;
           }
           else
           {
             turnRight();
           }          
         }
       }
       else
       {
         if(currentStepper == LEFT)
         {
           clearSteps = leftStepper.currentPosition() + stepsForTurn( currentTurn ); // so we go 90 degrees after we last see an obstacle
           turnLeft();
         }else{
           clearSteps = abs(rightStepper.currentPosition()) + stepsForTurn( currentTurn ); // so we go 90 degrees after we last see an obstacle
           turnRight(); 
         }
       }
     
       break; 
  }
  
}


void turnRandom(int n_min, int n_max)
{
//randomly L or R

          long r1 = random(0, 2);
          
//random turn amount 
          long r2 = random(n_min, n_max);
          Serial.print( "randoms: ");
          Serial.print(r1);
          Serial.print(  " and ");
          Serial.println(r2);
          currentTurn = r2;

          if(r1 == 0){
            currentStepper = LEFT;
          }else{
            currentStepper = RIGHT;
          }
}

void turnLeft()
{
  leftStepper.moveTo( leftStepper.currentPosition() + stepsForDistance( 50 )); // distance is a bit irrelevant, we will calculate a new destination next time round the loop
  rightStepper.moveTo( rightStepper.currentPosition() + stepsForDistance( 50 ));
}

void turnRight()
{
  leftStepper.moveTo( leftStepper.currentPosition() - stepsForDistance( 50 )); // distance is a bit irrelevant, we will calculate a new destination next time round the loop
  rightStepper.moveTo( rightStepper.currentPosition() - stepsForDistance( 50 ));
}

void go()
{
  leftStepper.moveTo( leftStepper.currentPosition()  - stepsForDistance( 50 ));
  rightStepper.moveTo( rightStepper.currentPosition() + stepsForDistance( 50 ));
}


