import java.util.*;
import java.util.List;

public class Node{
	
	private Node[] newNodes ;
	private Node posMove;
	private int[] N;
	
	
	public Node(int[] result){
		this.newNodes = new Node[result[0]]; // the newNodes that can be created
		this.posMove = posMove;// best possible move that algoritm can do
		this.N = new int[result[1]];//array that stores the current number of cards 

	}
	public Node[] getNewNodes(){
		
		return newNodes;
	}
	
	public Node getPosMove(){
		
		return posMove;
	}
	
	public int[] getN(){

		return N;
	}
	
	public void setN(int[] A){
		for(int i =0; i< N.length; i++){
			
			N[i]= A[i]; 
	
		}

	}
	public void setNewNodes(Node[] newNodes) {
		this.newNodes = newNodes;
	}
	public void setPosMove(Node posMove) {
		this.posMove = posMove;
	}

	
	// function that checks if the the array N is null 
	// if the array is null means that the game is over 
	public int checkN(){

		for(int i =0; i<N.length; i++){

			if(N[i] != 0){
				
				return 0;
			}
		}

	return 1;	
	}
		
}