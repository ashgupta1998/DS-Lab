#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;


	class AVL_Node{ 
	
	private: 
		 int key; 
		 int bf; 										// balance factor bf = height(left subtree) – height(right subtree) 
		 AVL_Node *LChild, *RChild; 
		AVL_Node()
		{
			LChild = NULL;
			RChild = NULL;
		}
		AVL_Node(int k)
		 {
		 	
		 	RChild = NULL;
		 	LChild = NULL;
		 	key = k;					
		 	bf = 0;	
		 }
	 
	 friend class AVL_Tree; 
	 
	 
	}; 
	
	class AVL_Tree{ 
	 private: 
	    AVL_Node *root = new AVL_Node();
		AVL_Node *head = new AVL_Node(0); 
		int a;
		 void LL_Rotate(AVL_Node *par,AVL_Node *par_par);
		 void RR_Rotate(AVL_Node *par,AVL_Node *par_par);
		 void LR_Rotate(AVL_Node *par,AVL_Node *par_par);
		 void RL_Rotate(AVL_Node *par,AVL_Node *par_par);
		 void AVL_Print2(AVL_Node *ptr, FILE *filename);
		 AVL_Node* copy(AVL_Node *root);
		 void destroy(AVL_Node* ptr);
	 public: 
		 AVL_Tree(); 
		 AVL_Tree(const AVL_Tree &T); 
		 AVL_Tree &operator=(const AVL_Tree &T); 
		 void AVL_Insert(int k); 
		 void AVL_Delete(int k); 
		 bool AVL_Search(int k); 
		 void AVL_Print(FILE *filename); 
		 ~AVL_Tree()
		 {
		 	destroy(head);
		 	
		 }
	}; 
	
	AVL_Tree :: AVL_Tree()
	{
		
		head ->RChild = NULL;							   //right child of head stores the root
		root = NULL;
	}
	
	AVL_Node * AVL_Tree:: copy(AVL_Node *root)					//copy function will recursively copy contents of one tree into another node by node
	{
		if (root == NULL)
			return NULL;
		else{
			AVL_Node* newNode = new AVL_Node(root->key);		//create a new node for new tree with key = key value of the node of the original tree 
			newNode->LChild = copy(root->LChild);				//Recursively create copy of left and right sub tree
    		newNode->RChild = copy(root->RChild);			
			return newNode;										//return new node created
		}
	}
	AVL_Tree :: AVL_Tree(const AVL_Tree &T)						//copy constructor which call copy function for copying one tree data into another
	{
		if(root == NULL)										//if tree is empty return nothing 
        	return ;
        else
		{
			AVL_Node* head2 = new AVL_Node();
			head2 = copy(head);									//head2 is head of new tree and copy(head) will copy contents of original tree into new tree
		 } 
    }
    
    AVL_Tree & AVL_Tree :: operator=(const AVL_Tree &T)			//assignment operator overloading; here suppose T1=T2 then assignment operator will place contents of T1 to T2 and destroy T1
    {
    	if(this != &T)											//if both trees are different 
    	{
			AVL_Node *head_new = new AVL_Node();			
			head_new = copy(T.root);							//make T2 as duplicate of T1 
	    	destroy(T.root);									//destroy original tree T1
    	}
    	return *this;											//return new tree
    	
	}
    
    void AVL_Tree::destroy(AVL_Node *ptr)						//it gets called when destructor is called
    {															//this function recursively deletes tree node by node
    	if (ptr == NULL)
    		return ;
    	else
    	{
    		if(ptr->LChild != NULL)
    		{
    			destroy(ptr->LChild);							//recursive call to left child
			}
			if(ptr->RChild != NULL)
			{
				destroy(ptr->RChild);							//recursive call to right child
			}
			delete(ptr);										//delete node
		}
	}
    
    
    

	void AVL_Tree::LL_Rotate(AVL_Node *par,AVL_Node *par_par)				
		 {
		 
		 	/*
		 	 below convention is followed	
		 			par_par									par_par
		 				 \										\
		 				  par									temp		
		 				/    \				==>   			   /	\
		 			   x	temp							par		 z
						   /	\						   /   \
						  y		 z 						  x    y	
			 
			 */	
		 															  
			AVL_Node *temp = new AVL_Node();									  
		 	temp = par->RChild;									     																		 
		 	par_par -> RChild = temp;
			par->RChild = temp->LChild;
			temp->LChild = par;
			root = head->RChild;
			temp->bf = 0;
			par->bf = 0;
															
		}
		
	void AVL_Tree::RR_Rotate(AVL_Node *par,AVL_Node *par_par)				
		 {	
		 /*
		 	 below convention is followed	
		 					par_par								   par_par
		 				   /									  /
		 				  par									temp		
		 				/    \				<==   			   /	\
		 			  temp	 x						          y    par		 
					 /	 \						                  /   \
			     	y	  z 						             z     x	
			 
			 */															   
			AVL_Node *temp = new AVL_Node();									  
		 	temp = par->LChild;
		 	if(par_par != head)
		 		par_par->LChild = temp;
		 	else 
			 	par_par -> RChild = temp;					//if par_par is head then it means par is root and hence par_par's right child is set and not left child 
			par->LChild = temp->RChild;
			temp->RChild = par;	
			par->bf = 0;
			root = head->RChild;
			par->bf=0;
			temp->bf=0;												
		}
		
	void AVL_Tree::LR_Rotate(AVL_Node *par,AVL_Node *par_par)
	{
		/*
		 	 below convention is followed	
		 					par_par								     par_par					par_par
		 				   /    \									  /	 \					  /      \
		 				  par	 a									par	  a	                temp2    a
		 				/    \				==>   			       /   \		==>		   /     \	
		 			  temp1	 x						             temp2   x		         temp1   par
					 /	 \						                /   \                   /    \  /  \ 
			     	y	  temp2 						     temp1   z     	            y     w z   x
			 			  /    \						   /	 \
						w      z	                       y    w
		 */		
		
		AVL_Node *temp1 = new AVL_Node();
		AVL_Node *temp2 = new AVL_Node();
		
		int bf_;
		temp1 = par->LChild;
		temp2 = temp1->RChild;
		bf_ = temp2->bf;
		if(bf_ == a)
		{
			par->bf = a;
			temp1->bf = 0;
		}
		else if (bf_ == 0)
		{
			par->bf = 0;
			temp1->bf = 0;
		}
		else
		{
			par->bf = 0;
			temp1->bf = -1*a;
		}
		par->LChild = temp2;
		temp1->RChild = temp2->LChild;
		temp2->LChild = temp1;
		root = head->RChild;
		if(par == par_par->LChild)
		{
			par_par->LChild = temp2;
			par->LChild = temp2->RChild;
			temp2->RChild = par;
		}
		else
		{
			par_par->RChild = temp2;
			par->LChild = temp2->RChild;
			temp2->RChild = par;
		}
		
		root = head->RChild;
		
   }
   void AVL_Tree::RL_Rotate(AVL_Node *par,AVL_Node *par_par)
	{
		
		/*
		 	 below convention is followed	
		 				par_par								   par_par						par_par
		 				/	\									  /	\					 	 /	  \	
		 			 par	a									par	a	                	temp2  a
		 		    /   \				==>   			 	  /   \				==>		   /     \	
		 		   y	 temp1	 						 	 y    temp2   		     	 par    temp1
					    /	  \				                 	  /  \              	/   \  /  \ 
			        temp2 	   x					         	 w   temp1        		y   w z   x
			 	   /    \						                	 /	  \
	   		      w      z	                                    	z      x
		*/	
		
		AVL_Node *temp1 = new AVL_Node();
		AVL_Node *temp2 = new AVL_Node();
		
		temp1 = par->RChild;
		temp2 = temp1->LChild;
		int bf_ = temp2->bf;
		if(bf_ == a)
		{
			par->bf = a;
			temp1->bf = 0;
		}
		else if (bf_ == 0)
		{
			par->bf = 0;
			temp1->bf = 0;
		}
		else
		{
			par->bf = 0;
			temp1->bf = -1*a;
		}
		par->RChild = temp2;
		temp1->LChild = temp2->RChild;
		temp2->RChild = temp1;
		root = head->RChild;
		if(par == par_par->LChild)
		{
			par_par->LChild = temp2;
			par->RChild = temp2->LChild;
			temp2->LChild = par;
			
		}
		else
		{
			par_par->RChild = temp2;
			par->RChild = temp2->LChild;
			temp2->LChild = par;
			
		}
		root = head->RChild;
		
		
   }
		
		
		 
	bool AVL_Tree::AVL_Search(int k )
	{
		AVL_Node *temp = new AVL_Node();
		temp = root;
		if(head->RChild == NULL)						//if tree is empty return false
		{
			return false;
		}
		
		else{
			temp = root;								//set temp as root
			while(temp != NULL)			
			{
				if(temp->key == k)
				{
					return true;						//return true as element found 
				}
				else if(temp->key < k)
				{
					temp = temp->RChild;				//using bst property, move to right subtree if temp->key < k
				}
				else
				{
					temp = temp->LChild;				//using bst property, move to left subtree if temp->key < k
				}
			}
			return false;								//if temp becomes NULL i.e. element is not found; return false 
		}
		
	}
	
	void AVL_Tree::AVL_Insert(int k)
	{
		
		AVL_Node *s = new AVL_Node();
		AVL_Node *t = new AVL_Node();
		AVL_Node *q = new AVL_Node();
		AVL_Node *p = new AVL_Node();
		AVL_Node *r = new AVL_Node();
		
		if(AVL_Search(k))									//if element exists alredy then return 
		{
			cout<<k<<" already exists "<<endl;
		}
		else
		{	
			cout<<"Element inserted"<<endl;
			s = t = head;									
		
			if(head->RChild == NULL)						//inserting k as root node
			{
				AVL_Node *node = new AVL_Node(k);
				root = node;
				root->key = k;								//setting value of root as k 
				root->RChild=NULL;
				root->LChild=NULL;
				
				head->RChild = root;
				int root_val;
				root_val = root->key;	
			}
			else
			{
				q = p =  head->RChild;
				AVL_Node *back_up = new AVL_Node();
			
				
			/*if node has bf as +1 or -1 then it is potential balancing node i.e. node where rebalancing may be required after insertion of new node	
			**s is potential balancing node 	
			finding potential balancing node s and its parent t 
			finding location where the node is to be inserted*/
			
			while(q!=NULL)
			{
				if(q != NULL && q->bf != 0)
				{
				
					back_up = p;							//useful in setting t later => as s is initialized as head so when we obtain first potential balancing node then t = s , t remains as head only
					t = s;									//finding s and t
					s = q;
					
				}
				p = q;
				if(q->key < k)
				{
					q = q->RChild;
				}
				else
				{
					q = q->LChild;
				}
				
				
			 } 
			 if(t == head && s!=head && s!= head->RChild)
			 	t = back_up;				    		//using back_up to find p in s is not the root or head and if t still is = head 
		
		AVL_Node *node = new AVL_Node(k);
		q = node;
		
	
		q->RChild = q->LChild = NULL;
		if(root == NULL)								// inserting new node as root as tree is empty
		{
			root = q;
			head->RChild = root;
		}
		else
		{
		
			if(p->key > k)
			{
				p->LChild = q;						//inserting new node as left child of its parent
			}
			else
			{
				p->RChild = q;						//inserting new node as right child of its parent
			}
		
			a = -1;									//setting a which will be useful in identifying type of rotation
			if(s!=head)
			{
				if(s->key > k)
				{
					a = 1;							//a will be useful for rotation				
					p = r = s->LChild;
				}
				else
				{
					p = r = s->RChild;	
				}
			}
			else
			{
				if(root->key>k)
				{
					a = 1;
					
				}
				p = r = root;
			}
			//changing balancing factor of nodes between s and q whose balancing factor was previously = 0
			while(p != q)
			{
				if(p->key > k)
				{
					p->bf = 1;
					p = p->LChild;
				}
				else
				{
					p->bf = -1;
					p = p-> RChild;
				}
		}
		
		if(s->bf == 0 && s!=head)
		{
			s->bf = a;
			head -> LChild += 1;
			return;
		}
		else if(s-> bf == -1*a && s!=head)
		{
			s->bf = 0;
			return;
		}
		else
		{
			if(s->bf == a && r->bf == a && s!=head)
			{
				// as both s and its child have same balance factor this implies that need either LL or RR rotations
				if(a == 1)
				{
					RR_Rotate(s,t);
				}
				else
				{
					LL_Rotate(s,t);
				}
			}
			else
			{
				// as both s and its child have same balance factor this implies that need either LR or RL rotations
				if(s!=head)
			
				{
				if(a == -1)
				{
					RL_Rotate(s,t);
				}
				else
				{
					LR_Rotate(s,t);
				}
			}
			}
			return;
		}
	}
	}
	}
	}
	
	void AVL_Tree:: AVL_Delete(int k)
	{
		if(!AVL_Search(k))									//if element does not exist then return
		{
			cout<<"Element does not exits in the tree "<<endl;
			return;
		}
		else
		{
			cout<<"Element deleted"<<endl;
			AVL_Node* stack_[100];							//used to store the nodes which are traversed from head to node(k) and to its inorder successor if required
			AVL_Node *par = new AVL_Node();
			AVL_Node *temp = new AVL_Node();
			AVL_Node *q = new AVL_Node();
			AVL_Node *par_par = new AVL_Node();
			bool flag = false;
			int c=0;
			
			int i=0;
			stack_[i++] = head;								//push head into stack		
			q = head->RChild;								//set q = root
			while(q->key != k)
			{												//keep pushing nodes in stack until node k is reached
				if(q->key < k)
				{
					stack_[i++] = q;
					q = q->RChild;
				}
				else{
					stack_[i++] = q;
					q = q->LChild;
				}
			}
			
			//node k can be leaf node or node with single child or node with two children
		
			
			if(q->LChild == NULL || q->RChild == NULL )			//node(k) has single child or no child
			{
				temp = q->LChild?q->LChild:q->RChild;	
			
				if(temp == NULL)								//no child
				{
					par = stack_[i-1];
					if(par->key > k)
					{
						par->LChild = NULL;
						par->bf += -1;							//as k present as left child so reduce balance factor of its parent by 1
					}
					else
					{
						par->RChild = NULL;						//as k present as right child so increase balance factor of its parent by 1
						par->bf += 1;
					}
					free(q);									//delete node(k)
				}
				
				else											//node(k) has one child
				{
					par = stack_[i-1];							
					if(par->RChild == q)						//node (k) has right child
					{
						par->RChild->key = temp->key;			
						free(temp);
						
					}
					else
					{
						par->LChild->key = temp->key;
						free(temp);
					}
					
							q->LChild = NULL;					//as q is now replaced with its only child so setting its left,right pointer to NULL
							q->RChild = NULL;
							q->bf = 0;
							head->RChild = root;
							
						
				}
				if(par->bf == -1 || par->bf == 1 || par->bf ==0)
						i=i-1;										//as node par has been balanced so remove it from the stack 
				else flag = true;
			}
			else
			{
				// node k has two children
				
				AVL_Node * p = new AVL_Node;
				p = stack_[i-1]; 
				stack_[i++] = q;								   //q points the element to be deleted
				temp = q->RChild;
				while(temp->LChild != NULL)
				{
					
					stack_[i++] = temp;
					//p = stack_[i-1];
					temp = temp->LChild;
				}
				q->key = temp->key;								 	//copying successor's data in node(k)
				
				if(((temp->LChild == NULL && temp->RChild == NULL)  && temp == stack_[i-1]->LChild))
					q->bf = q->bf + 1;
					
				else if((temp->LChild == NULL && temp->RChild != NULL) && temp == stack_[i-1]->RChild)
						{
							if(stack_[i-1] == q)
								q->bf = q->bf + 2;								//incremented by 2 beacause later it will be reduced again
							else
								q->bf = q->bf + 1;
							if(q->LChild->bf == 1 ||q->LChild->bf == -1)		//height not changed
							{
								if(p!=head)
									p->bf += -1;
							}
						}
				else
					if((temp->LChild == NULL && temp->RChild == NULL) && temp == stack_[i-1]->RChild)
						q->bf = q->bf + 1;
							
				
				if(temp->RChild != NULL)
				{
					temp->key = temp->RChild->key;
					AVL_Node *n = new AVL_Node();
					free(n);
					temp->RChild = NULL;
					temp->bf = 0;
					flag = false;
					c=2;
				}
				else
				{
					if(stack_[i-1]->key <= temp->key)
						stack_[i-1]->RChild = NULL;
					else
						stack_[i-1]->LChild = NULL;
					if(stack_[i-1]!=root)
					{
						flag = false;
						c=2;
					}
					else
					{
						flag = true;
					}
					
					free(temp);
					
				}
			}
				int j;
				//chaning balancing factor of elements in stack and checking if rotaion required or not
				bool flag2 = false;
					if(flag == false)
					{
						flag2 = true;
					}
				for(j=i-1;j>=1;j--)
				{
					par = stack_[j];
					par_par = stack_[j-1];
							
					
					if(!flag && flag2)
					{
				
						if(par->key < k)
						{
							par->bf += 1;
						}
						else
						{
							par->bf += -1;
						}
						
						
						if(c==2)
						{
							if(stack_[j-1] == q)
								flag2 = false;
							else
								flag2 = true;
						}
						else
						{
							flag2 = false;
						}
					}	
					
					{
						if(c ==0 && flag == false)
							flag2 = true;
						AVL_Node * bf_change = new AVL_Node();
						int bf_change_bf=0;
						if(par->bf >1 && par->LChild != NULL && par->LChild->bf >= 0)			//Right right rotation required
						{
							bf_change = par->LChild;
							bf_change_bf = bf_change->bf;
							RR_Rotate(par,par_par);
							if(bf_change_bf == 0)
							{
							
								bf_change->bf = -1;
								par->bf = 1;
							}
							else
							{
						
								bf_change->bf = 0;
								par->bf = 0;
						}
							
						}
						else if(par->bf > 1 && par->LChild != NULL && par->LChild->bf < 0)  	//Left Right Rotation required
						{
							bf_change = par->LChild;
							bf_change_bf = bf_change->bf;
							LR_Rotate(par,par_par);
							bf_change->bf = 0;
							par->bf = 0;
							
						}
						else if(par->bf < -1 && par->RChild != NULL && par->RChild->bf <= 0)	//Left left Rotation required
						{
							bf_change = par->RChild;
							bf_change_bf = bf_change -> bf;
							LL_Rotate(par,par_par);
							if(bf_change_bf == 0){
							
								bf_change->bf = 1;
								par->bf = -1;
							}
							else{
						
								bf_change->bf = 0;
							par->bf = 0;
						}
							
						}
						else
						{
							if(par->bf < -1 && par->RChild != NULL && par->RChild >0)			//Right Left Rotation required
								{
								bf_change = par->RChild;
								bf_change_bf = bf_change -> bf;
								RL_Rotate(par,par_par);
								bf_change->bf = 0;
								par->bf = 0;
							}
								
						}	
						
					}
				}
				
			}
			
			
			
		}
	

	void AVL_Tree::AVL_Print2(AVL_Node *ptr, FILE *filename)
	{
		
		if(!ptr)
		{
			
			
		}
		if(ptr->LChild!=NULL)
		{
			fprintf(filename,"%d [label = \"<left> | <mid> %d | bf: %d | <right> \"];\n",ptr->LChild->key,ptr->LChild->key,ptr->LChild->bf);
			fprintf(filename,"\"%d\":left -> \"%d\":mid ;\n",ptr->key,ptr->LChild->key);
			AVL_Print2(ptr->LChild,filename);
		}	
		if(ptr->RChild!=NULL)
		{
			fprintf(filename,"%d [label = \"<left> |<mid> %d | bf: %d | <right> \"];\n",ptr->RChild->key,ptr->RChild->key,ptr->RChild->bf);
			fprintf(filename," \"%d\":right -> \"%d\": mid;\n",ptr->key,ptr->RChild->key);
			AVL_Print2(ptr->RChild,filename);
		}
			
	}
	
	void AVL_Tree::AVL_Print(FILE *filename)
	{
		fprintf(filename, "digraph AVL {\n");
        fprintf(filename, "    node [fontname=Arial , shape = record];\n");
        if (!head->RChild)
        	fprintf(filename, "\n");
        else
		{
        	fprintf(filename,"%d [label = \"<left> | <mid> %d | bf: %d | <right> \"];\n",root->key,root->key,root->bf);
			AVL_Print2(head->RChild,filename);
        }
        fprintf(filename, "}\n");
	}
	
	
	int main()
	{
		char choice;
		int operation;
		AVL_Tree avl;
		do{
			cout<<"Enter 1.Search 2. Insert 3.Delete 4.Print "<<endl;
			cin>>operation;
			cout<<"selected operation is : "<<operation<<endl;
			int k;
			switch(operation)
			{
				case 1:
					cout<<"Enter element to be searched: ";
					cin>>k;
					bool flag;
					flag = avl.AVL_Search(k);
					if(flag)
					{
						cout<<"Element found"<<endl;
					}
					else
						cout<<"Element not found"<<endl;
					break;
					
				case 2:
					cout<<"Enter element to be inserted: ";
					cin>>k;
					avl.AVL_Insert(k);
					break;
				
				case 3:
					cout<<"Enter element to be deleted: ";
					cin>>k;
					avl.AVL_Delete(k);
					break;
				case 4:
					cout<<"Printing tree"<<endl;
					FILE *fptr;
					fptr = fopen("avl1.dot","w");
					avl.AVL_Print(fptr);
					fclose(fptr);
					break;
				default:
					cout<<"Invalid choice"<<endl;
					break;
			}
			cout<<"Start (y/n): ";
			cin>>choice;
			while(choice!='y' && choice!='n')
			{
				cout<<"Invalid choice"<<endl;
				cout<<"Start (y/n): ";
				cin>>choice;
			}
			}while(choice!='n');
			
					return 0;
	}
	
	
	

