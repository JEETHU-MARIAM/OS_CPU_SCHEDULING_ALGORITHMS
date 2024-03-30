#include<stdio.h>
#include<stdlib.h>
struct list
{
	int at;
	int bt;
	int rt;
	int ct;
	int tat;
	int wt;
	int st;
    int p;
    int pri;
    int visited;
	struct list *next;
};
typedef struct list node;

node *create(node *head1,int n)
{
       node *newnode,*p;
       int at,bt,i,c,pr;
	   for(i=1;i<=n;i++)
	   {
	   		  newnode=(node *)malloc(sizeof(node));
	   		  printf("ENTER THE PROCESS NUMBER");
	   		  scanf("%d",&newnode->p);
	   	      printf("ENTER  THE ARRIVAL TIME, BURST TIME AND PRIORITY :");
	          scanf("%d%d%d",&at,&bt,&pr);
	          newnode->at=at;
	          newnode->bt=bt;
	          newnode->pri=pr;
	          if(head1==NULL || at<head1->at)
	          {
	          	newnode->next=head1;
	          	head1=newnode;
			  }
			  else
			  {
			  	p=head1;
			  	while(p->next!=NULL && p->next->at<at)
			  	{
			  	    p=p->next;	
				}
				newnode->next=p->next;
				p->next=newnode;
			}
	   }	
	   return(head1);
}

void display(node *head)
{
	node *p;
	p=head;
	printf("PROCESS\tARRIVAL TIME\tBURST TIME\tSTART TIMR\tRESP TIME\tCOMP TIME\tTAT TIME\t WAITING TIME\n");
	while(p!=NULL)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p->p,p->at,p->bt,p->st,p->rt,p->ct,p->tat,p->wt);
		p=p->next;
	}
}

void fcfs(node *head,int n)
{
	node *p1;
	p1=head;
	int i=0,q=0;
	float avgw=0,avgr=0,avgc=0,avgtat=0;
	printf("\n\n||FIRST COME FIRST SERVE|| \n");
	while(p1!=NULL)
	{
		printf("%d\t",p1->p);
		p1=p1->next;
	}
	p1=head;
	while(p1!=NULL)
	{
		if(i==0)
		{
			p1->st=p1->at;
			q=p1->st+p1->bt;
		}
		else
		{
			if(q<p1->at)
			{
				p1->st=p1->at;
				q=p1->st+p1->bt;
			}
			else
			{
				p1->st=q;
				q=p1->st+p1->bt;
			}
		}
		p1=p1->next;
		i++;
	}
	p1=head;
	while(p1!=NULL)
	{
		p1->rt=p1->st-p1->at;
		p1->ct=p1->st+p1->bt;
		p1->tat=p1->ct-p1->at;
		p1->wt=p1->tat-p1->bt;
		avgr=avgr+p1->rt;
		avgc=avgc+p1->ct;
		avgtat=avgtat+p1->tat;
		avgw=avgw+p1->wt;
		p1=p1->next;
	}
	avgr=avgr/n;
	avgc=avgc/n;
	avgw=avgw/n;
	avgtat=avgtat/n;
	printf("\nAVERGAGE WAITING TIME    :%f\n",avgw);
	printf("AVERGAGE COMPLETION TIME   :%f\n",avgc);
	printf("AVERGAGE TAT TIME          :%f\n",avgtat);
	printf("AVERGAGE RESPONSE TIME     :%f\n",avgr);
    display(head);
    printf("\n---------------------------------------------------------------------------\n");
}

node *sjf(node *head,int n)
{
	node *q1,*q2,*temp,*sjfhead,*sjf,*q3;
	int bt_min,count=0,i=0,j=0,q=0,loop=0;
	float avgr=0,avgw=0,avgtat=0,avgc=0;
	q1=head;
	q2=q1->next;
	bt_min=q1->bt;
	while(q2!=NULL)//finding the min bt for the same at
	{
		if(q1->at==q2->at && bt_min>q2->bt)
		{
			bt_min=q2->bt;
		}
		q2=q2->next;
	}
	q2=head;
	while(q2!=NULL)//initializing 0 for all visited
	{
		q2->visited=0;
		q2=q2->next;
	}
	while(q1!=NULL && count==0)//finding the st for the first process
	{
		if(q1->bt==bt_min && q1->visited!=1)
		{
			q1->visited=1;
			q1->st=q1->at;
			
			q=q1->st+q1->bt;
			count++;
			temp=(node *)malloc(sizeof(node));
			sjfhead=temp;
			sjf=temp;
			temp->p=q1->p;
			temp->at=q1->at;
			temp->bt=q1->bt;
		}
		q1=q1->next;
	}
	for(i=0;i<n-1;i++)//for the rest of the process
	{
		q3=head;
		j=0;
		while(q3!=NULL && q3->visited==1)//to skip the visited process
		{
			q3=q3->next;
		}
		while(q3!=NULL && q < q3->at)//for the process whose at>q; q is the ct of prev process
		{
			q3->visited=1;
			q3->st=q3->at;
			q=q3->st+q3->bt;
			temp=(node *)malloc(sizeof(node));
		   	temp->p=q3->p;
			temp->at=q3->at;
			temp->bt=q3->bt;
			sjf->next=temp;
	        sjf=sjf->next;
		    temp->next=NULL;
			q3=q3->next;
		}
		while(q3!=NULL && q3->at<=q) //finding bt_min among rest of the process whose at is within the q of prev process
		{
			if(q3->visited==1)
			{
				q3=q3->next;
			}
			else
			{
				if(j==0)
				{
					bt_min=q3->bt;
				}
				else
				{
					if(bt_min>q3->bt)
					{
						bt_min=q3->bt;
					}
				}
				q3=q3->next;
				j++;
			}
		}
		q1=head;
		count=0;
		while(q1!=NULL && 0==count)//finding st of the required process
	    {
		       if(q1->bt==bt_min && q1->visited!=1)
		       {
		        	q1->visited=1;
			        q1->st=q;
			        q=q1->st+q1->bt;
		          	count++;
		          	loop++;
			       temp=(node *)malloc(sizeof(node));
		        	temp->p=q1->p;
			        temp->at=q1->at;
			        temp->bt=q1->bt;
			        sjf->next=temp;
			        sjf=sjf->next;
			        temp->next=NULL;
		       }
		      q1=q1->next;
	   }
	}
	printf("\n\n||SHORTEST JOB FIRST||\n");
	q2=sjfhead;
	while(q2!=NULL)
	{
		printf("%d\t",q2->p);
		q2=q2->next;
	}
	q1=head;
	while(q1!=NULL)
	{
		q1->rt=q1->st-q1->at;
		q1->ct=q1->st+q1->bt;
		q1->tat=q1->ct-q1->at;
		q1->wt=q1->tat-q1->bt;
		avgr=avgr+q1->rt;
		avgc=avgc+q1->ct;
		avgtat=avgtat+q1->tat;
		avgw=avgw+q1->wt;
		q1=q1->next;
	}
	printf("\n\n");
	display(head);
	avgr=avgr/n;
	avgc=avgc/n;
	avgw=avgw/n;
	avgtat=avgtat/n;
	printf("\nAVERGAGE WAITING TIME    :%f\n",avgw);
	printf("AVERGAGE COMPLETION TIME   :%f\n",avgc);
	printf("AVERGAGE TAT TIME          :%f\n",avgtat);
	printf("AVERGAGE RESPONSE TIME     :%f\n",avgr);
	printf("\n--------------------------------------------------------------------------\n");
}

void priority(node *head,int n)
{
	node *pq1,*pq2,*temp,*phead,*ps;
	int i,pri_min=0,q=0,j=0,count=0;
	float avgr=0,avgw=0,avgtat=0,avgc=0;
	pq1=head;
	pq2=pq1->next;
	pri_min=pq1->pri;
	while(pq2!=NULL)
	{
		if(pq1->at==pq2->at && pri_min>pq2->pri)
		{
			pri_min=pq2->pri;
		}
	    pq2=pq2->next;
	}
	while(pq1!=NULL)
	{
		pq1->visited=0;
		pq1=pq1->next;
	}
	pq1=head;
	while(pq1!=NULL && count==0)
	{
		if(pq1->pri==pri_min && pq1->visited!=1)
		{
			pq1->visited=1;
			pq1->st=pq1->at;
			q=pq1->st+pq1->bt;
			count++;
			temp=(node *)malloc(sizeof(node));
			phead=temp;
			ps=temp;
			temp->p=pq1->p;
			temp->at=pq1->at;
			temp->bt=pq1->bt;
			temp->pri=pq1->pri;
		}
		pq1=pq1->next;
	}
	for(i=0;i<n-1;i++)
	{
		pq1=head;
		j=0;
		while(pq1!=NULL && pq1->visited==1)
		{
			pq1=pq1->next;
		}
		while(pq1!=NULL && q < pq1->at)
		{
			pq1->visited=1;
			pq1->st=pq1->at;
			q=pq1->st+pq1->bt;
			temp=(node *)malloc(sizeof(node));
		   	temp->p=pq1->p;
			temp->at=pq1->at;
			temp->bt=pq1->bt;
			temp->pri=pq1->pri;
			ps->next=temp;
	        ps=ps->next;
		    temp->next=NULL;
			pq1=pq1->next;
		}
		while(pq1!=NULL && pq1->at<=q)
		{
			if(pq1->visited==1)
			{
				pq1=pq1->next;
			}
			else
			{
				if(j==0)
				{
					pri_min=pq1->pri;
				}
				else
				{
					if(pri_min>pq1->pri)
					{
						pri_min=pq1->pri;
					}
				}
				pq1=pq1->next;
				j++;
			}
		}
		pq1=head;
		count=0;
		while(pq1!=NULL && 0==count)
	    {
		       if(pq1->pri==pri_min && pq1->visited!=1)
		       {
		        	pq1->visited=1;
			        pq1->st=q;
			        q=pq1->st+pq1->bt;
		          	count++;
			       temp=(node *)malloc(sizeof(node));
		        	temp->p=pq1->p;
			        temp->at=pq1->at;
			        temp->bt=pq1->bt;
			        temp->pri=pq1->pri;
			        ps->next=temp;
			        ps=ps->next;
			        temp->next=NULL;
		       }
		      pq1=pq1->next;
	   }
	}
	printf("\n\n||PRIORITY SCHEDULING||\n");
	pq2=phead;
	while(pq2!=NULL)
	{
		printf("%d\t",pq2->p);
		pq2=pq2->next;
	}
	pq1=head;
	while(pq1!=NULL)
	{
		pq1->rt=pq1->st-pq1->at;
		pq1->ct=pq1->st+pq1->bt;
		pq1->tat=pq1->ct-pq1->at;
		pq1->wt=pq1->tat-pq1->bt;
		avgr=avgr+pq1->rt;
		avgc=avgc+pq1->ct;
		avgtat=avgtat+pq1->tat;
		avgw=avgw+pq1->wt;
		pq1=pq1->next;
	}
	printf("\n\n");
	display(head);
	avgr=avgr/n;
	avgc=avgc/n;
	avgw=avgw/n;
	avgtat=avgtat/n;
	printf("\nAVERGAGE WAITING TIME    :%f\n",avgw);
	printf("AVERGAGE COMPLETION TIME   :%f\n",avgc);
	printf("AVERGAGE TAT TIME          :%f\n",avgtat);
	printf("AVERGAGE RESPONSE TIME     :%f\n",avgr);
	printf("\n--------------------------------------------------------------------------\n");
}

void roundrobin(node *head,int n)
{
	node *p1,*temp,*p2,*t1,*thead;
	int q[n],pid=0,front,rear,i=0,j=0,tq,count;
	float avgr=0,avgw=0,avgtat=0,avgc=0;
	p1=head;
	printf("Enter time quantam:");
	scanf("%d",&tq);
	while(p1!=NULL)//making all visited 0
	{
		p1->visited=0;
		p1=p1->next;
	}
	p1=head;
	front=rear=0;//fot the first process
	q[rear]=p1->p;
	p1->visited=1;
	while(front!=-1)//rr
	{
		pid=q[front];
		p1=head;
		j=0;
		while(p1!=NULL && j==0)//only execute once at a time;temp updation,queue insertion
		{
			if(p1->p==pid)
			{
					temp=(node *)malloc(sizeof(node));
				if(i==0)//for first proc
				{
					p1->st=p1->at;
					temp->st=p1->at;
					if(tq<=p1->bt)
					{
						p1->ct=tq+p1->st;
						temp->p=pid;
						temp->ct=tq+p1->st;
						p1->bt=p1->bt-tq;
						temp->bt=p1->bt;
					}
					else
					{
						p1->ct=p1->bt+p1->st;
						temp->ct=p1->bt;
						temp->bt=p1->bt=0;
					}
					thead=temp;
					t1=thead;
					temp->next=NULL;
					i=9;
					front=rear=-1;
				}
				else//for rest process and deleting from queue
				{
					temp->st=t1->ct;
					temp->p=pid;
					if(tq<=p1->bt)
					{
						temp->ct=tq+temp->st;
						p1->bt=p1->bt-tq;
						p1->ct=temp->ct;
					}
					else
					{
						temp->ct=p1->bt+temp->st;
						p1->bt=0;
						p1->ct=temp->ct;
					}
					temp->bt=p1->bt;
					t1->next=temp;
					t1=t1->next;
					temp->next=NULL;
					if(front==rear)
					{
						front=rear=-1;
					}
					else
					{
						front=(front+1)%n;
					}
				}
				p2=p1->next;//inser into queue based on proc list
				while(p2!=NULL)
				{
					if(p2->at<=t1->ct && p2->visited!=1)
					{
						if(front==-1)
						{
							front=0;
						}
						rear=(rear+1)%n;
						q[rear]=p2->p;
						p2->visited=1;
					}p2=p2->next;
				}
				if(t1->bt!=0)//insert into queue based on temp bt
				{
					if(front==-1)
					{
						front=0;
					}
					rear=(rear+1)%n;
					q[rear]=t1->p;
				}
				j++;
			}
			p1=p1->next;
			             if(front==-1)
			             {
			             	p2=head;
			             	count=0;
			             	while(p2!=NULL && count==0)
			             	{
			             	        if(t1->ct<p2->at && p2->visited==0)
									 {
									        p2->visited=1;
											front=0;
											if(rear=-1)
											rear=0;
											else
											rear=(rear+1)%n;
											q[rear]=p2->p;
											count++; 	
									 }	
								//	 else
									 p2=p2->next;
							}
						 }
		}
	}
	printf("\n\n||ROUND ROBIN||\n\n");
	t1=thead;
	while(t1!=NULL)
	{
		printf("%d\t",t1->p);
		t1=t1->next;
	}
	t1=thead;
	p1=head;
	while(p1!=NULL && t1!=NULL)
	{
		if(p1->p==t1->p && p1->visited==1)
		{
			p1->st=t1->st;
			p1->bt=t1->bt+tq;
			p1->visited=0;
			p1=p1->next;
		}
		t1=t1->next;
	}
	p1=head;
	while(p1!=NULL)
	{
		p1->rt=p1->st-p1->at;
		p1->tat=p1->ct-p1->at;
		p1->wt=p1->tat-p1->bt;
		avgr=avgr+p1->rt;
		avgc=avgc+p1->ct;
		avgtat=avgtat+p1->tat;
		avgw=avgw+p1->wt;
		p1=p1->next;
	}
	printf("\n\n");
	display(head);
	avgr=avgr/n;
	avgc=avgc/n;
	avgw=avgw/n;
	avgtat=avgtat/n;
	printf("\nAVERGAGE WAITING TIME    :%f\n",avgw);
	printf("AVERGAGE COMPLETION TIME   :%f\n",avgc);
	printf("AVERGAGE TAT TIME          :%f\n",avgtat);
	printf("AVERGAGE RESPONSE TIME     :%f\n",avgr);
	printf("\n______________________________________________________________________\n");
}
int main()
{
	int n;
	node *h;
	h=NULL;
	printf("enter the number of process");
	scanf("%d",&n);
	h=create(h,n);
	fcfs(h,n);
	sjf(h,n);
	priority(h,n);
	roundrobin(h,n);
}
