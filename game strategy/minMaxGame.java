//KOTOFOLI CHRISTINA, A.M:4087
//TSAPIKOUNI GEORGIA , A.M:4304
import java.util.Scanner;
import java.util.*;
import java.util.List;



public class minMaxGame{
	
	public static int[] A; // array that contains for each team the number of cards
	public static int[] B; // array that contains the max number of cards which can be removed from each team 
	public static int valueMax = 1; 
	public static int valueMin = -1;
	public static int[] result;

	
	
	public static int[] Inputs(){
		
		Scanner input1 = new Scanner(System.in);
		System.out.println("Give the number of cards M : ");
		int M = input1.nextInt();
		while(M <= 0 || M > 13){
			System.out.println("Please give a positive number less than 14");
			M = input1.nextInt();
		}
        System.out.println("Give the number of teams K:");
        int Klength = input1.nextInt();
		while(Klength <= 0 || Klength > 4){
			System.out.println("Please give a number of team less than 5");
			Klength = input1.nextInt();
		}
		int[] result = new int[2];
		result[0] = M;
		result[1] = Klength;
        A = new int[Klength];
		B = new int[Klength];

		System.out.println("Deal the cards to each group ");
		int sum = 0;
		do{
			sum = 0;
			for(int i = 0; i < Klength; i++){
				
				System.out.println("Enter the number of cards for team  A" + i + ":");
				int K = input1.nextInt();
				while(K < 2){
					
					System.out.println("Please enter more than one card for team " + i);
					K = input1.nextInt();
					
				}
				
				A[i] = K;
				
				
				System.out.println("Enter the number of total cards that you want to remove from this team : ");
				int numCards_B = input1.nextInt();
				while( numCards_B >= K){
					
					System.out.println("Please enter B<A ");
					numCards_B = input1.nextInt();
					
				}
				B[i] = numCards_B;
	
				
			
				sum += A[i];	

			}
			if(sum != M) 
			{
				System.out.println("M is not equal to the sum of values in array A");
				
				
			}
		}while(sum != M);
	

	return result; 	// return an array which contain the number of cards and the number of teams
	}
	
	// method that copy all the elements of an array to another array 
	public static void copy(int[] array1 , int[] array2){
		
		for(int i =0; i < array1.length; i++){
			
			array2[i] = array1[i];
			
			
		}
		
	}
	public static int MinMaxAlgorithm(Node parent , int nextPlayer){
		
		
		int removedCards = 0; 
		int k = 0;
		int nextPl =0;
		int bestChild=0;
		
		int[] nodes = new int[result[0]];
		Node[] layers =  new Node[result[0]];
		
		Node choosenChild ;
		
		for(int i = 0; i < A.length; i++){
			
			if( parent.getN()[i] > 0 ){
	
				if(B[i]<(parent.getN()[i])){
					
					removedCards = B[i];

				}else{
					
					removedCards = parent.getN()[i];
				}
				
				for(int j =1; j <= removedCards; j++){ // for each card that we can remove we create a node 
			
					Node childNode = new Node(result); // create a new node 
					childNode.setN(new int[result[0]]);
					copy(parent.getN(), childNode.getN());//copy the cards of the parent to the child 
					childNode.getN()[i] = childNode.getN()[i] - j; // remove j cards from the i team 
					parent.getNewNodes()[k] = childNode; 
					nodes[k] = MinMaxAlgorithm(childNode, nextPl); // recursively call of minMaxAlgorith for creating new childNode
					layers[k] = childNode;// an array that contains all the childNode
					k++;
					
				}
			}
		}
		
		if(nextPlayer == valueMax && parent.checkN()==1){
			
			return(-1);
		}
		else if(nextPlayer == valueMin && parent.checkN()==1){
			
			return(+1);
		}
		
		if(nextPlayer == valueMax){ 
			
			nextPl = valueMin;
		}else{
			
			nextPl = valueMax;
		}
	
		
		if(nextPlayer == valueMax){ //if the nextPlayer is in the layer of valueMax
			
			bestChild = nodes[0];
			choosenChild = layers[0];
			for(int i = 1; i< k; i++){
				if(nodes[i] > bestChild){
					bestChild = nodes[i]; // we find the maxvalue of the nodes and store it  in bestchild
					choosenChild= layers[i];	
				}
			}
		}else{ //if the nextPlayer is in the layer of valueMin
			bestChild = nodes[0];
			choosenChild = layers[0];
			for(int i = 1; i< k; i++){
				if(nodes[i] < bestChild){
					
					bestChild = nodes[i];//we find the minvalue of the nodes and store it in the bestchild
					choosenChild= layers[i];	
				}
			}
		}
		
		
	parent.setPosMove(choosenChild);// we set to the parent the best posMove to do 
	return bestChild ;
	
	}
	
	public static void main(String[] args){
		
		result = Inputs();
		Scanner input1 = new Scanner(System.in);
		Node root = new Node(result);
		root.setN(A);
		int[] N = root.getN();
		Node pos = root.getPosMove();
		int nextPlayer = valueMax;
		
		for(int i =0; i< A.length; i++){
			
			root.getN()[i]= A[i]; // fill the root of the game , the size has given by the user 
			
		}
		
		System.out.println("-----------START THE GAME --------------------");
		System.out.printf("Initial cards and teams of the Game \n");
		
		for(int i =0 ; i < A.length; i++){
			
			System.out.println("Team " + i + " has "  +  " " + root.getN()[i] + " cards");
		
		}
		
		while(true){
			
			
			//check if the nextplayer is the pc and if there is not any card to play, then user is the winner 
			if(nextPlayer == valueMax  && root.checkN()== 1){
				
				System.out.printf("\n\n");
				System.out.printf("USER IS THE WINNER!!\n");
				System.out.printf("--END OF THE GAME--");
				break;
			}//check if the nextplayer is the user and if there is not any card to play, then pc is the winner 
			else if(nextPlayer == valueMin  && root.checkN()==1){
				
				System.out.printf("\n\n");
				System.out.printf("PC IS THE WINNER\n");
				System.out.printf("--END OF THE GAME--");
				break;
			}
			else if(nextPlayer == valueMax ){//if the pc has cards to play call the MINMAXALGORITHM
				
				System.out.printf("------------------------------------------- \n");
				System.out.printf("--TURN OF PC--\n");
				MinMaxAlgorithm(root,valueMax);
				root = root.getPosMove();
				
				for (int i = 0;i < A.length;i++)
				{
					System.out.println("Team " + i + " has "  +  " " + root.getN()[i] + " cards");
				}
			nextPlayer = valueMin;	
			
			}
			else{//if user has cards to play then do all the steps bellow like choosing team , ask for the number of cargs that have to be removed 

				System.out.printf("\n CHOOSE TEAM FOR REMOVING CARDS\n"); 
				for (int i = 0;i <A.length;i++){
 
					if (root.getN()[i] > 0){
						
						System.out.printf("Removing from team " + i + " press " + i + "\n");
						
					}
				}
				int new_team = input1.nextInt();
				while(new_team >= A.length ){
					System.out.println("Please give a valid team ");
					new_team = input1.nextInt();
				}
				
				if (B[new_team] < (root.getN()[new_team])){
					
					System.out.printf("Remove 1 to " + B[new_team] + " cards \n");
					
					int cards_removed = input1.nextInt();
					while(cards_removed< 1 || cards_removed > B[new_team]){
						
						System.out.println("Please give a positive number less than or equal " +B[new_team]);
						cards_removed = input1.nextInt();
					}
					root.getN()[new_team] = root.getN()[new_team] - cards_removed;	
				}
				else{
					
					System.out.printf("Remove 1 to " +  root.getN()[new_team] + " cards \n");
					int cards_removed = input1.nextInt();
					while(cards_removed< 1 || cards_removed > root.getN()[new_team]){
						System.out.println("Please give a positive number less than or equal " + root.getN()[new_team]);
						cards_removed = input1.nextInt();
					}
					root.getN()[new_team] = root.getN()[new_team] - cards_removed;
				}
	
				System.out.printf("------------------------------------------- \n");
				System.out.printf("--TURN OF USER--\n");
				for (int i = 0;i < A.length;i++){
	
					System.out.println("Team " + i + " has "  +  " " + root.getN()[i] + " cards");
				}
				nextPlayer = valueMax;
			}
		}
	}
}