###############################################
C File for converting from RE to Minimal DFA and its simulation
###############################################
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200

struct nfa_state
{
int a, b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, eps1, eps2;
}NFA[MAX], DFA[MAX], min_DFA[MAX/2];

struct state_group
{
	int state[MAX];
}DFA_group[MAX/2], final, final_min_dfa;

int current,final_state,start_state, dfa_states, min_dfa_states;
int stack [MAX];
int top;
//---------------------------------------infix to postfix begin-------------------------------------------------------------
int top_expr = -1;
char stack_expr[MAX+3];
void push_expr(char item);
char pop_expr();
int is_operator(char symbol);
int precedence(char symbol);

void print_group(struct state_group cur){
	int i;
	for(i = 0;i< MAX;i++)
	{
		printf("%d ",cur.state[i] );
	}
	printf("\n");
}

void minimal_DFA()
{
	int i, j, i1, j1, check = 1, number_of_states, minimization_table[dfa_states][dfa_states], check2 = 0;
	/*
	for(i = 0;i<dfa_states;i++)	//seperate the final and non final states
	{
		//if(final.state[i] = )
		if(final.state[i] != 1)
			mindfa[0].state[i] = 1;
		else
			mindfa[1].state[i] = 1;
	}*/
	for(i=0;i<MAX/2;i++)
    {
        min_DFA[i].a = min_DFA[i].b = min_DFA[i].c = min_DFA[i].d = min_DFA[i].e = min_DFA[i].f = min_DFA[i].g = min_DFA[i].h = min_DFA[i].i = min_DFA[i].j = min_DFA[i].k = min_DFA[i].l = -1;
        min_DFA[i].m = min_DFA[i].n = min_DFA[i].o = min_DFA[i].p = min_DFA[i].q = min_DFA[i].r = min_DFA[i].s = min_DFA[i].t = min_DFA[i].u = min_DFA[i].v = min_DFA[i].w = min_DFA[i].x = -1;
        min_DFA[i].y = min_DFA[i].z = min_DFA[i].eps1 = min_DFA[i].eps2 = -1;
        final_min_dfa.state[i] = -1;
        final_min_dfa.state[MAX-1 -i] = -1;
    }
	for(i = 1; i < dfa_states; i++)
	{
		for(j = 0; j < i; j++)	
		{
			if((final.state[j] == 1 && final.state[i] != 1) || (final.state[i] == 1 && final.state[j] != 1))
				minimization_table[i][j] = 1;
		}
	}
	while(check != 0)  //loop until there is a change
	{
		check = 0;
		for(i = 1; i < dfa_states; i++)
		{
			for(j = 0; j < i; j++)	
			{
				if(minimization_table[i][j] != 1)
				{
					if(DFA[i].a != -1 && DFA[j].a != -1)
					{
						if(minimization_table[DFA[i].a][DFA[j].a] == 1 || minimization_table[DFA[j].a][DFA[i].a] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].b != -1 && DFA[j].b != -1)
					{
						if(minimization_table[DFA[i].b][DFA[j].b] == 1 || minimization_table[DFA[j].b][DFA[i].b] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].c != -1 && DFA[j].c != -1)
					{
						if(minimization_table[DFA[i].c][DFA[j].c] == 1 || minimization_table[DFA[j].c][DFA[i].c] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].d != -1 && DFA[j].d != -1)
					{
						if(minimization_table[DFA[i].d][DFA[j].d] == 1 || minimization_table[DFA[j].d][DFA[i].d] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].e != -1 && DFA[j].e != -1)
					{
						if(minimization_table[DFA[i].e][DFA[j].e] == 1 || minimization_table[DFA[j].e][DFA[i].e] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].f != -1 && DFA[j].f != -1)
					{
						if(minimization_table[DFA[i].f][DFA[j].f] == 1 || minimization_table[DFA[j].f][DFA[i].f] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].g != -1 && DFA[j].g != -1)
					{
						if(minimization_table[DFA[i].g][DFA[j].g] == 1 || minimization_table[DFA[j].g][DFA[i].g] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].h != -1 && DFA[j].h != -1)
					{
						if(minimization_table[DFA[i].h][DFA[j].h] == 1 || minimization_table[DFA[j].h][DFA[i].h] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].i != -1 && DFA[j].i != -1)
					{
						if(minimization_table[DFA[i].i][DFA[j].i] == 1 || minimization_table[DFA[j].i][DFA[i].i] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].j != -1 && DFA[j].j != -1)
					{
						if(minimization_table[DFA[i].j][DFA[j].j] == 1 || minimization_table[DFA[j].j][DFA[i].j] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].k != -1 && DFA[j].k != -1)
					{
						if(minimization_table[DFA[i].k][DFA[j].k] == 1 || minimization_table[DFA[j].k][DFA[i].k] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].l != -1 && DFA[j].l != -1)
					{
						if(minimization_table[DFA[i].m][DFA[j].m] == 1 || minimization_table[DFA[j].m][DFA[i].m] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].m != -1 && DFA[j].m != -1)
					{
						if(minimization_table[DFA[i].m][DFA[j].m] == 1 || minimization_table[DFA[j].m][DFA[i].m] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].n != -1 && DFA[j].n != -1)
					{
						if(minimization_table[DFA[i].a][DFA[j].a] == 1 || minimization_table[DFA[j].a][DFA[i].a] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].o != -1 && DFA[j].o != -1)
					{
						if(minimization_table[DFA[i].o][DFA[j].o] == 1 || minimization_table[DFA[j].o][DFA[i].o] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].p != -1 && DFA[j].p != -1)
					{
						if(minimization_table[DFA[i].p][DFA[j].p] == 1 || minimization_table[DFA[j].p][DFA[i].p] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].q != -1 && DFA[j].q != -1)
					{
						if(minimization_table[DFA[i].q][DFA[j].q] == 1 || minimization_table[DFA[j].q][DFA[i].q] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].r != -1 && DFA[j].r != -1)
					{
						if(minimization_table[DFA[i].r][DFA[j].r] == 1 || minimization_table[DFA[j].r][DFA[i].r] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].s != -1 && DFA[j].s != -1)
					{
						if(minimization_table[DFA[i].s][DFA[j].s] == 1 || minimization_table[DFA[j].s][DFA[i].s] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].t != -1 && DFA[j].t != -1)
					{
						if(minimization_table[DFA[i].t][DFA[j].t] == 1 || minimization_table[DFA[j].t][DFA[i].t] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].u != -1 && DFA[j].u != -1)
					{
						if(minimization_table[DFA[i].u][DFA[j].u] == 1 || minimization_table[DFA[j].u][DFA[i].u] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].a != -1 && DFA[j].a != -1)
					{
						if(minimization_table[DFA[i].v][DFA[j].v] == 1 || minimization_table[DFA[j].v][DFA[i].v] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].w != -1 && DFA[j].w != -1)
					{
						if(minimization_table[DFA[i].w][DFA[j].w] == 1 || minimization_table[DFA[j].w][DFA[i].w] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].x != -1 && DFA[j].x != -1)
					{
						if(minimization_table[DFA[i].x][DFA[j].x] == 1 || minimization_table[DFA[j].x][DFA[i].x] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].y != -1 && DFA[j].y != -1)
					{
						if(minimization_table[DFA[i].y][DFA[j].y] == 1 || minimization_table[DFA[j].y][DFA[i].y] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
					if(DFA[i].z != -1 && DFA[j].z != -1)
					{
						if(minimization_table[DFA[i].z][DFA[j].z] == 1 || minimization_table[DFA[j].z][DFA[i].z] == 1)
						{
							minimization_table[i][j] = 1;
							check = 1;
						}
					}
				}		
			}  //till here we have created the distinct table

			// check2++;
			/*for(i1 = 1; i1 < dfa_states; i1++)
			{
				for(j1 = 0; j1 < i1; j1++)	
				{
					printf("%d\t", minimization_table[i1][j1]);
				}
				printf("\n");
			}
			printf("\n");
			if(check2 >= 3)
				return;*/
		}
	}
	struct state_group mindfa[100], taken_states;
	int state_number = 0;
	for(i = 0; i< MAX;i++)
	{
		taken_states.state[i] = -1;
	}
	for(i = 0; i<dfa_states;i++)
	{
		check = 0;
		if(taken_states.state[i] == -1)
		{
			for(j = 0; j<i ;j++)
			{
				if(minimization_table[i][j] == 0)
				{
					if(taken_states.state[j] != -1)
					{
						mindfa[taken_states.state[j]].state[i] = 1;
						taken_states.state[i] = taken_states.state[j];
						check = 1;
						break;
					}
				}
			}
			if(check == 0)
			{
				mindfa[state_number].state[i] = 1;
				taken_states.state[i] = state_number;
				state_number++;
			}
			for(j = 0; j<i ;j++)
			{
				if(minimization_table[i][j] == 0)
				{
					if(taken_states.state[j] == -1)
					{
						mindfa[taken_states.state[i]].state[j] = 1;
						taken_states.state[j] = taken_states.state[i];
					}
				}
			}
		}
	}/*
	for(i = 0 ;i < dfa_states;i++)
	{
		printf("%d\n", taken_states.state[i]);
	}
	printf("%d\n", state_number);*/
	// print_group(taken_states);
	min_dfa_states = state_number;
	for(i = 0; i< state_number;i++)
	{
		for(j = 0;j<dfa_states;j++)
		{
			if(taken_states.state[j] == i)
				break;
		}
		if(DFA[j].a != -1)
			min_DFA[i].a = taken_states.state[DFA[j].a];
		if(DFA[j].b != -1)
			min_DFA[i].b = taken_states.state[DFA[j].b];
		if(DFA[j].c != -1)
			min_DFA[i].c = taken_states.state[DFA[j].c];
		if(DFA[j].d != -1)
			min_DFA[i].d = taken_states.state[DFA[j].d];
		if(DFA[j].e != -1)
			min_DFA[i].e = taken_states.state[DFA[j].e];
		if(DFA[j].f != -1)
			min_DFA[i].f = taken_states.state[DFA[j].f];
		if(DFA[j].g != -1)
			min_DFA[i].g = taken_states.state[DFA[j].g];
		if(DFA[j].h != -1)
			min_DFA[i].h = taken_states.state[DFA[j].h];
		if(DFA[j].i != -1)
			min_DFA[i].i = taken_states.state[DFA[j].i];
		if(DFA[j].j != -1)			
			min_DFA[i].j = taken_states.state[DFA[j].j];
		if(DFA[j].k != -1)
			min_DFA[i].k = taken_states.state[DFA[j].k];
		if(DFA[j].l != -1)
			min_DFA[i].l = taken_states.state[DFA[j].l];
		if(DFA[j].m != -1)
			min_DFA[i].m = taken_states.state[DFA[j].m];
		if(DFA[j].n != -1)
			min_DFA[i].n = taken_states.state[DFA[j].n];
		if(DFA[j].o != -1)
			min_DFA[i].o = taken_states.state[DFA[j].o];
		if(DFA[j].p != -1)
			min_DFA[i].p = taken_states.state[DFA[j].p];
		if(DFA[j].q != -1)
			min_DFA[i].q = taken_states.state[DFA[j].q];
		if(DFA[j].r != -1)
			min_DFA[i].r = taken_states.state[DFA[j].r];
		if(DFA[j].s != -1)
			min_DFA[i].s = taken_states.state[DFA[j].s];
		if(DFA[j].t != -1)
			min_DFA[i].t = taken_states.state[DFA[j].t];
		if(DFA[j].u != -1)
			min_DFA[i].u = taken_states.state[DFA[j].u];
		if(DFA[j].v != -1)
			min_DFA[i].v = taken_states.state[DFA[j].v];
		if(DFA[j].w != -1)
			min_DFA[i].w = taken_states.state[DFA[j].w];
		if(DFA[j].x != -1)
			min_DFA[i].x = taken_states.state[DFA[j].x];
		if(DFA[j].y != -1)
			min_DFA[i].y = taken_states.state[DFA[j].y];
		if(DFA[j].z != -1)
			min_DFA[i].z = taken_states.state[DFA[j].z];
	}
	// print_group(taken_states);
	// print_group(final);
	for(i=0;i<dfa_states;i++)
	{
		if(final.state[i] == 1)
		{
			final_min_dfa.state[taken_states.state[i]] = 1;
		}
	}
}



struct state_group closure(struct state_group cur, int state)
{
	int nw = 1, temp[200], cnt = 0, top = 1, i;
	struct state_group new_state;
	new_state = cur;
	temp[cnt]=state;
	new_state.state[state] = 1;
	while(nw != 0)
	{
		if(NFA[temp[cnt]].eps1 != -1){
			new_state.state[NFA[temp[cnt]].eps1] = 1;
			temp[top] = NFA[temp[cnt]].eps1;
			top++;
			nw++;
		}
		if(NFA[temp[cnt]].eps2 != -1){
			new_state.state[NFA[temp[cnt]].eps2] = 1;	
			nw++;
			temp[top] = NFA[temp[cnt]].eps2;
			top++;
		}
		nw--;
		cnt++;
	}
	return new_state;
}
struct state_group move(struct state_group cur, char c)  //returns the group of states corresponding to input group of states and input symbol c
{
	struct state_group temp;
	int i;
	for(i = 0; i< MAX;i++)
	{
		temp.state[i] = -1;
	}
	for(i = 0; i< MAX;i++)
	{
		if(cur.state[i] == 1)
		{
			if(c == 'a')
			{
				if(NFA[i].a != -1 )
				{
					temp.state[NFA[i].a] = 1;
					temp = closure(temp, NFA[i].a);
				}
			}
			if(c== 'b')
			{
				if(NFA[i].b != -1 )
				{
					temp.state[NFA[i].b] = 1;
					temp  =closure(temp, NFA[i].b);
				}
			}
			if(c== 'c')
			{
				if(NFA[i].c != -1 )
				{
					temp.state[NFA[i].c] = 1;
					temp  =closure(temp, NFA[i].c);
				}
			}
			if(c== 'd')
			{
				if(NFA[i].d != -1 )
				{
					temp.state[NFA[i].d] = 1;
					temp  =closure(temp, NFA[i].d);
				}
			}
			if(c== 'e')
			{
				if(NFA[i].e != -1 )
				{
					temp.state[NFA[i].e] = 1;
					temp  =closure(temp, NFA[i].e);
				}
			}
			if(c== 'f')
			{
				if(NFA[i].f != -1 )
				{
					temp.state[NFA[i].f] = 1;
					temp  =closure(temp, NFA[i].f);
				}
			}
			if(c== 'g')
			{
				if(NFA[i].g != -1 )
				{
					temp.state[NFA[i].g] = 1;
					temp  =closure(temp, NFA[i].g);
				}
			}
			if(c== 'h')
			{
				if(NFA[i].h != -1 )
				{
					temp.state[NFA[i].h] = 1;
					temp  =closure(temp, NFA[i].h);
				}
			}
			if(c== 'i')
			{
				if(NFA[i].i != -1 )
				{
					temp.state[NFA[i].i] = 1;
					temp  =closure(temp, NFA[i].i);
				}
			}
			if(c== 'j')
			{
				if(NFA[i].j != -1 )
				{
					temp.state[NFA[i].j] = 1;
					temp  =closure(temp, NFA[i].j);
				}
			}
			if(c== 'k')
			{
				if(NFA[i].k != -1 )
				{
					temp.state[NFA[i].k] = 1;
					temp  =closure(temp, NFA[i].k);
				}
			}
			if(c== 'l')
			{
				if(NFA[i].l != -1 )
				{
					temp.state[NFA[i].l] = 1;
					temp  =closure(temp, NFA[i].l);
				}
			}
			if(c== 'm')
			{
				if(NFA[i].m != -1 )
				{
					temp.state[NFA[i].m] = 1;
					temp  =closure(temp, NFA[i].m);
				}
			}
			if(c== 'n')
			{
				if(NFA[i].n != -1 )
				{
					temp.state[NFA[i].n] = 1;
					temp  =closure(temp, NFA[i].n);
				}
			}
			if(c== 'o')
			{
				if(NFA[i].o != -1 )
				{
					temp.state[NFA[i].o] = 1;
					temp  =closure(temp, NFA[i].o);
				}
			}
			if(c== 'p')
			{
				if(NFA[i].p != -1 )
				{
					temp.state[NFA[i].p] = 1;
					temp  =closure(temp, NFA[i].p);
				}
			}
			if(c== 'q')
			{
				if(NFA[i].q != -1 )
				{
					temp.state[NFA[i].q] = 1;
					temp  =closure(temp, NFA[i].q);
				}
			}
			if(c== 'r')
			{
				if(NFA[i].r != -1 )
				{
					temp.state[NFA[i].r] = 1;
					temp  =closure(temp, NFA[i].r);
				}
			}
			if(c== 's')
			{
				if(NFA[i].s != -1 )
				{
					temp.state[NFA[i].s] = 1;
					temp  =closure(temp, NFA[i].s);
				}
			}
			if(c== 't')
			{
				if(NFA[i].t != -1 )
				{
					temp.state[NFA[i].t] = 1;
					temp  =closure(temp, NFA[i].t);
				}
			}
			if(c== 'u')
			{
				if(NFA[i].u != -1 )
				{
					temp.state[NFA[i].u] = 1;
					temp  =closure(temp, NFA[i].u);
				}
			}
			if(c== 'v')
			{
				if(NFA[i].v != -1 )
				{
					temp.state[NFA[i].v] = 1;
					temp  =closure(temp, NFA[i].b);
				}
			}


			if(c== 'w')
			{
				if(NFA[i].w != -1 )
				{
					temp.state[NFA[i].w] = 1;
					temp  =closure(temp, NFA[i].w);
				}
			}
			if(c== 'x')
			{
				if(NFA[i].x != -1 )
				{
					temp.state[NFA[i].x] = 1;
					temp  =closure(temp, NFA[i].x);
				}
			}
			if(c== 'y')
			{
				if(NFA[i].y != -1 )
				{
					temp.state[NFA[i].y] = 1;
					temp  =closure(temp, NFA[i].y);
				}
			}
			if(c== 'z')
			{
				if(NFA[i].z != -1 )
				{
					temp.state[NFA[i].z] = 1;
					temp  =closure(temp, NFA[i].z);
				}
			}


		}
	}
	return temp;
}	

int compare_state_group(struct state_group state1, struct state_group state2)
{
	int i;
	for(i=0;i<MAX;i++)
	{
		if(state1.state[i] != state2.state[i])
			return 0;
	}
	return 1;
}

int check_state(struct state_group state) //checks if the input state is exisiting in the state_group
{
	int i;
	for(i = 0 ;i < MAX/2; i++)
	{
		if(compare_state_group(DFA_group[i], state))
			return 0;
	}
	return 1;
}

int get_state(struct state_group state)  //returns the state number corresponding to the ipnut state
{
	int i;
	for(i = 0 ;i < MAX/2; i++)
	{
		if(compare_state_group(DFA_group[i], state))
			return i;
	}
}

int check_empty(struct state_group state) //checks if the current state is empty
{
	int i, check = 0;
	for(i=0;i<MAX;i++)
	{
		if(state.state[i] == 1)
			return 1;
	}
	return 0;
}


void create_dfa()
{
	int i;
	char inp[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for(i=0;i<MAX;i++)
    {
        DFA[i].a = DFA[i].b = DFA[i].c = DFA[i].d = DFA[i].e = DFA[i].f = DFA[i].g = DFA[i].h = DFA[i].i = DFA[i].j = DFA[i].k = DFA[i].l = -1;
        DFA[i].m = DFA[i].n = DFA[i].o = DFA[i].p = DFA[i].q = DFA[i].r = DFA[i].s = DFA[i].t = DFA[i].u = DFA[i].v = DFA[i].w = DFA[i].x = -1;
        DFA[i].y = DFA[i].z = DFA[i].eps1 = DFA[i].eps2 = -1;
        final.state[i] = -1;
    }
    int newstate = 1,number_of_states = 1, cur_state = 0;
    DFA_group[0].state[start_state] = 1;
  	DFA_group[0] = closure(DFA_group[0], start_state);
    while(newstate != 0)
    {
    	int j;
    	for(j = 0; j<26; j++)
    	{
    		struct state_group temp = move(DFA_group[cur_state], inp[j]);
    		//print_group(temp);
    		//return;
    		if(check_empty(temp))
    		{
    			if(check_state(temp))
    			{
	    			DFA_group[number_of_states] = temp;
	    			number_of_states++;
	    			newstate++;
	    		}
				if(inp[j]== 'a')
	   				DFA[cur_state].a = get_state(temp);
				if(inp[j]== 'b')
				    DFA[cur_state].b = get_state(temp);
				if(inp[j]== 'c')
				    DFA[cur_state].c = get_state(temp);
				if(inp[j]== 'd')
				    DFA[cur_state].d = get_state(temp);
				if(inp[j]== 'e')
				    DFA[cur_state].e = get_state(temp);
				if(inp[j]== 'f')
				    DFA[cur_state].f = get_state(temp);
				if(inp[j]== 'g')
				    DFA[cur_state].g = get_state(temp);
				if(inp[j]== 'h')
				    DFA[cur_state].h = get_state(temp);
				if(inp[j]== 'i')
				    DFA[cur_state].i = get_state(temp);
				if(inp[j]== 'j')
				    DFA[cur_state].j = get_state(temp);
				if(inp[j]== 'k')
				    DFA[cur_state].k = get_state(temp);
				if(inp[j]== 'l')
				    DFA[cur_state].l = get_state(temp);
				if(inp[j]== 'm')
				    DFA[cur_state].m = get_state(temp);
				if(inp[j]== 'n')
				    DFA[cur_state].n = get_state(temp);
				if(inp[j]== 'o')
				    DFA[cur_state].o = get_state(temp);
				if(inp[j]== 'p')
				    DFA[cur_state].p = get_state(temp);
				if(inp[j]== 'q')
				    DFA[cur_state].q = get_state(temp);
				if(inp[j]== 'r')
				    DFA[cur_state].r = get_state(temp);
				if(inp[j]== 's')
				    DFA[cur_state].s = get_state(temp);
				if(inp[j]== 't')
				    DFA[cur_state].t = get_state(temp);
				if(inp[j]== 'u')
				    DFA[cur_state].u = get_state(temp);
				if(inp[j]== 'v')
				    DFA[cur_state].v = get_state(temp);
				if(inp[j]== 'w')
				    DFA[cur_state].w = get_state(temp);
				if(inp[j]== 'x')
				    DFA[cur_state].x = get_state(temp);
				if(inp[j]== 'y')
				    DFA[cur_state].y = get_state(temp);
				if(inp[j]== 'z')
				    DFA[cur_state].z = get_state(temp);
			}
			if(DFA_group[cur_state].state[final_state] != -1)
				final.state[cur_state] = 1;
    	}
    	newstate--;
    	cur_state++;
    }
    final.state[0] = -1;
    //printf("%d\n", number_of_states);
    dfa_states = number_of_states;
}

void push_expr(char item)
{
 if(top_expr >= MAX-1)
 {
  printf("\nStack Overflow. Push not possible.\n");
 }
 else
 {
  top_expr = top_expr+1;
  stack_expr[top_expr] = item;
 }
}
char pop_expr()
{
 char item = NULL;
 if(top_expr <= -1)
 {
  printf("\nStack Underflow. Pop not possible.\n");
 }
 else
 {
  item = stack_expr[top_expr];
  stack_expr[top_expr] = NULL;
  top_expr = top_expr-1;
 }
 return(item);
}
int is_operator(char symbol)
{
 if(symbol == '.' || symbol == '+')
 {
  return 1;
 }
 else
 {
  return 0;
 }
}
int precedence(char symbol)
{

if(symbol == '+' || symbol == '.')
 {
  return(1);
 }
 else
 {
  return(0);
 }
}
//-------------------------------------------infix to postfix end-------------------------------------------------
void push(int val)
{
    stack[++top] = val;
}

int pop()
{
    return stack[top--];
}

void init_nfa_table()
{
    int i;
    for(i=0;i<MAX;i++)
    {
        NFA[i].a = NFA[i].b = NFA[i].c = NFA[i].d = NFA[i].e = NFA[i].f = NFA[i].g = NFA[i].h = NFA[i].i = NFA[i].j = NFA[i].k = NFA[i].l = -1;
        NFA[i].m = NFA[i].n = NFA[i].o = NFA[i].p = NFA[i].q = NFA[i].r = NFA[i].s = NFA[i].t = NFA[i].u = NFA[i].v = NFA[i].w = NFA[i].x = -1;
        NFA[i].y = NFA[i].z = NFA[i].eps1 = NFA[i].eps2 = -1;
    }
}
void alphabet(char c)
{
if(c== 'a')
NFA[current].a = current+1;

if(c== 'b')
NFA[current].b = current+1;


if(c== 'c')
NFA[current].c = current+1;

if(c== 'd')
NFA[current].d = current+1;


if(c== 'e')
NFA[current].e = current+1;

if(c== 'f')
NFA[current].f = current+1;


if(c== 'g')
NFA[current].g = current+1;

if(c== 'h')
NFA[current].h = current+1;


if(c== 'i')
NFA[current].i = current+1;

if(c== 'j')
NFA[current].j = current+1;

if(c== 'k')
NFA[current].k = current+1;


if(c== 'l')
NFA[current].l = current+1;

if(c== 'm')
NFA[current].m = current+1;


if(c== 'n')
NFA[current].n = current+1;

if(c== 'o')
NFA[current].o = current+1;


if(c== 'p')
NFA[current].p = current+1;

if(c== 'q')
NFA[current].q = current+1;


if(c== 'r')
NFA[current].r = current+1;

if(c== 's')
NFA[current].s = current+1;

if(c== 't')
NFA[current].t = current+1;


if(c== 'u')
NFA[current].u = current+1;

if(c== 'v')
NFA[current].v = current+1;


if(c== 'w')
NFA[current].w = current+1;

if(c== 'x')
NFA[current].x = current+1;


if(c== 'y')
NFA[current].y = current+1;

if(c== 'z')
NFA[current].z = current+1;

push(current);
push(current+1);

current += 2;
}

void concat()
{
int start_first, start_second, end_first, end_second;

end_second = pop();
start_second = pop();
end_first = pop();
start_first = pop();

NFA[end_first].eps1 = start_second;

push(start_first);
push(end_second);
}

void OR()
{
int start_first, start_second, end_first, end_second;

end_second = pop();
start_second = pop();
end_first = pop();
start_first = pop();
NFA[current].eps1 = start_first;
NFA[current].eps2 = start_second;
NFA[end_first].eps1 = current + 1;
NFA[end_second].eps1 = current + 1;

push(current);
push(current + 1);
current += 2;
}

void star()
{
int start_first, end_first;

end_first = pop();
start_first = pop();
NFA[current].eps1 = start_first;
NFA[current].eps2 = current + 1;
NFA[end_first].eps1 = start_first;
NFA[end_first].eps2 = current + 1;

push(current);
push(current + 1);
current += 2;
}

void construct_nfa(char* expr)
{
    int  i = 0;
    for(i=0;expr[i]!='\0';i++)
    {
        switch(expr[i])
        {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            alphabet(expr[i]);
            break;
            case '.':
            concat();
            break;
            case '+':
            OR();
            break;
            case '*':
            star();
            break;
        }
    }
    final_state = pop();
    start_state = pop();
}

void display_NFA()
{
    int i;
    printf("\nstate\ta\tb\tc\td\te\tf\tg\th\ti\tj\tk\tl\tm\tn\to\tp\tq\tr\ts\tt\tu\tv\tw\tx\ty\tz\teps");
	for(i=0;i<current;i++)
	{
		if(i==start_state)
		printf("\n->%d",i);
		else
		if(i==final_state)
		printf("\n* %d",i);
		else
		printf("\n %d",i);

		if(NFA[i].a==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].a);

		if(NFA[i].b==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].b);

		if(NFA[i].c==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].c);

		if(NFA[i].d==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].d);

		if(NFA[i].e==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].e);

		if(NFA[i].f==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].f);

		if(NFA[i].g==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].g);

		if(NFA[i].h==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].h);


		if(NFA[i].i==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].i);

		if(NFA[i].j==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].j);

		if(NFA[i].k==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].k);

		if(NFA[i].l==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].l);

		if(NFA[i].m==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].m);

		if(NFA[i].n==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].n);

		if(NFA[i].o==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].o);

		if(NFA[i].p==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].p);


		if(NFA[i].q==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].q);

		if(NFA[i].r==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].r);


		if(NFA[i].s==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].s);

		if(NFA[i].t==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].t);

		if(NFA[i].u==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].u);

		if(NFA[i].v==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].v);

		if(NFA[i].w==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].w);

		if(NFA[i].x==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].x);

		if(NFA[i].y==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].y);

		if(NFA[i].z==-1)
		printf("\t-");
		else
		printf("\t{%d}",NFA[i].z);


		if(NFA[i].eps1!=-1)
		{
		printf("\t{%d",NFA[i].eps1);
		if(NFA[i].eps2!=-1)
		{
		printf(",%d",NFA[i].eps2);
		}
		printf("}");
		}
		else
		printf("\t-");
	}
}

void display_min_DFA()
{
    int i;
    printf("\nstate\ta\tb\tc\td\te\tf\tg\th\ti\tj\tk\tl\tm\tn\to\tp\tq\tr\ts\tt\tu\tv\tw\tx\ty\tz");
	for(i=0;i<min_dfa_states;i++)
	{
		printf("\n %d",i);

		if(min_DFA[i].a==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].a);

		if(min_DFA[i].b==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].b);

		if(min_DFA[i].c==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].c);

		if(min_DFA[i].d==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].d);

		if(min_DFA[i].e==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].e);

		if(min_DFA[i].f==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].f);

		if(min_DFA[i].g==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].g);

		if(min_DFA[i].h==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].h);
		if(min_DFA[i].i==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].i);

		if(min_DFA[i].j==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].j);

		if(min_DFA[i].k==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].k);

		if(min_DFA[i].l==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].l);

		if(min_DFA[i].m==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].m);

		if(min_DFA[i].n==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].n);

		if(min_DFA[i].o==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].o);

		if(min_DFA[i].p==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].p);


		if(min_DFA[i].q==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].q);

		if(min_DFA[i].r==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].r);


		if(min_DFA[i].s==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].s);

		if(min_DFA[i].t==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].t);

		if(min_DFA[i].u==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].u);

		if(min_DFA[i].v==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].v);

		if(min_DFA[i].w==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].w);

		if(min_DFA[i].x==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].x);

		if(min_DFA[i].y==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].y);

		if(min_DFA[i].z==-1)
		printf("\t-");
		else
		printf("\t{%d}",min_DFA[i].z);
	}
	printf("\n");
	printf("Accepting States are: ");
	for(i = 0;i<MAX;i++)
	{
		if(final_min_dfa.state[i] == 1)
			printf("%d\t", i);
	}
}

void display_DFA()
{
    int i;
    printf("\nstate\ta\tb\tc\td\te\tf\tg\th\ti\tj\tk\tl\tm\tn\to\tp\tq\tr\ts\tt\tu\tv\tw\tx\ty\tz");
	for(i=0;i<dfa_states;i++)
	{
		printf("\n %d",i);

		if(DFA[i].a==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].a);

		if(DFA[i].b==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].b);

		if(DFA[i].c==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].c);

		if(DFA[i].d==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].d);

		if(DFA[i].e==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].e);

		if(DFA[i].f==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].f);

		if(DFA[i].g==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].g);

		if(DFA[i].h==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].h);


		if(DFA[i].i==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].i);

		if(DFA[i].j==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].j);

		if(DFA[i].k==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].k);

		if(DFA[i].l==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].l);

		if(DFA[i].m==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].m);

		if(DFA[i].n==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].n);

		if(DFA[i].o==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].o);

		if(DFA[i].p==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].p);


		if(DFA[i].q==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].q);

		if(DFA[i].r==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].r);


		if(DFA[i].s==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].s);

		if(DFA[i].t==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].t);

		if(DFA[i].u==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].u);

		if(DFA[i].v==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].v);

		if(DFA[i].w==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].w);

		if(DFA[i].x==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].x);

		if(DFA[i].y==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].y);

		if(DFA[i].z==-1)
		printf("\t-");
		else
		printf("\t{%d}",DFA[i].z);
	}
	printf("\n");
	printf("Accepting States are: ");
	for(i = 0;i<MAX;i++)
	{
		if(final.state[i] == 1)
			printf("%d\t", i);
	}
}

int main()
{
char expr[MAX];

printf("Rules:\n1)\".\" is used for concatenation\n2)\"+\" is used for OR\n3)\"*\" is used for iterator\n");
printf("\nEnter the Regular Expression: ");
scanf("%s",expr);
init_nfa_table();
//-------------------------------------------------infix to postfix begin---------------------------------------------------------------
char infix_expr[MAX + 3];
strcpy(infix_expr,"(");
strcat(infix_expr,expr);
strcat(infix_expr,")");
int i=0,j=0;
char postfix_expr[MAX + 3];
char item, x;
item = infix_expr[i++];
while(item != '\0')
{

    if(item == '(')
        {
           push_expr(item);
        }
    else if ((item >= 'a' && item <= 'z') || (item == '*'))
        {
            postfix_expr[j++] = item;
        }
    else if(is_operator(item) == 1)
        {
            x=pop_expr();
            while(is_operator(x) == 1 && precedence(x)>= precedence(item))
            {
                postfix_expr[j++] = x;
                x = pop_expr();
            }
            push_expr(x);
            push_expr(item);
        }
    else if(item == ')')
        {
            x = pop_expr();
            while(x != '(')
            {
                postfix_expr[j++] = x;
                x = pop_expr();
            }
        }
    else
        {
            printf("\nInvalid Regular Expression.\n");
            getchar();
            exit(0);
        }
    item = infix_expr[i++];
}
postfix_expr[j++] = '\0';
printf("\nRegular expression in Postfix notation: ");
puts(postfix_expr);
getchar();

//-----------------------------------------------------------infix to postfix end-------------------------------------------------------------------
printf("\n");
construct_nfa(postfix_expr);
create_dfa();
printf("NFA corresponding to the given RE");
display_NFA();
printf("\n\n");
printf("DFA corresponding to NFA");
display_DFA();
printf("\n\n");
printf("Minimal DFA");
minimal_DFA();
display_min_DFA();
printf("\n");
while(1)
{
	printf("Give input \"exit\" to terminate\n");
	printf("Enter String: ");
	char s[MAX];
	scanf("%s", s);
	if (strcmp(s,"exit")==0)
		{
			printf("Bye!!!");
			exit(EXIT_SUCCESS);
		}
	int i = 0, current_state = 0, len = strlen(s), check = 0;
	for(i = 0;i<len;i++)
	{
		printf("%d ",current_state );
		printf("-(%c)-> ", s[i]);
		if(s[i] == 'a')
		{
			if(min_DFA[current_state].a != -1)
				current_state = min_DFA[current_state].a;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'b')
		{
			if(min_DFA[current_state].b != -1)
				current_state = min_DFA[current_state].b;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'c')
		{
			if(min_DFA[current_state].c != -1)
				current_state = min_DFA[current_state].c;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'd')
		{
			if(min_DFA[current_state].d != -1)
				current_state = min_DFA[current_state].d;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'e')
		{
			if(min_DFA[current_state].e != -1)
				current_state = min_DFA[current_state].e;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'f')
		{
			if(min_DFA[current_state].f != -1)
				current_state = min_DFA[current_state].f;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'g')
		{
			if(min_DFA[current_state].g != -1)
				current_state = min_DFA[current_state].g;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'h')
		{
			if(min_DFA[current_state].h != -1)
				current_state = min_DFA[current_state].a;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'i')
		{
			if(min_DFA[current_state].i != -1)
				current_state = min_DFA[current_state].i;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'j')
		{
			if(min_DFA[current_state].j != -1)
				current_state = min_DFA[current_state].j;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'k')
		{
			if(min_DFA[current_state].k != -1)
				current_state = min_DFA[current_state].k;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'l')
		{
			if(min_DFA[current_state].l != -1)
				current_state = min_DFA[current_state].l;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'm')
		{
			if(min_DFA[current_state].m != -1)
				current_state = min_DFA[current_state].m;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'n')
		{
			if(min_DFA[current_state].n != -1)
				current_state = min_DFA[current_state].n;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'o')
		{
			if(min_DFA[current_state].o != -1)
				current_state = min_DFA[current_state].o;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'p')
		{
			if(min_DFA[current_state].p != -1)
				current_state = min_DFA[current_state].p;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'q')
		{
			if(min_DFA[current_state].q != -1)
				current_state = min_DFA[current_state].q;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'r')
		{
			if(min_DFA[current_state].r != -1)
				current_state = min_DFA[current_state].r;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 's')
		{
			if(min_DFA[current_state].s != -1)
				current_state = min_DFA[current_state].s;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 't')
		{
			if(min_DFA[current_state].t != -1)
				current_state = min_DFA[current_state].t;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'u')
		{
			if(min_DFA[current_state].u != -1)
				current_state = min_DFA[current_state].u;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'v')
		{
			if(min_DFA[current_state].v != -1)
				current_state = min_DFA[current_state].v;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'w')
		{
			if(min_DFA[current_state].w != -1)
				current_state = min_DFA[current_state].w;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'x')
		{
			if(min_DFA[current_state].x != -1)
				current_state = min_DFA[current_state].x;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'y')
		{
			if(min_DFA[current_state].y != -1)
				current_state = min_DFA[current_state].y;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		else if(s[i] == 'z')
		{
			if(min_DFA[current_state].z != -1)
				current_state = min_DFA[current_state].z;
			else{
				printf("No Move\n");check = 1;
				break;
			}
		}
		
	}
	if(check == 0){
		printf("%d\n", current_state);
	if(final_min_dfa.state[current_state] == 1)
		printf("String Accepted\n");
	else
		printf("String Not Accepted\n");
	}
	else{
		printf("String Not Accepted\n");
	}


	
}
/*struct state_group temp;
closure(temp, start_state);
print_group(temp);*/
}

//-----------infix to postfix--


//----------infix to postfix---

