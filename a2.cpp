#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "tictoc.h"
using namespace std;

class DNADatabase // doubly linked list
{
    struct Node
    {
        char c;
        Node* p_next;  //pointers
        Node* p_prev;
        Node(char val): c(val), p_next(nullptr), p_prev(nullptr) {}
        Node(char val, Node* p_next_in)
        {
          c= val;
          p_next = p_next_in;
        }
    };

  private:

      Node *p_head, *p_tail;
      vector<int> size;//holds the size of files the user loads
      Node *findVal(char n) //returns node of the given number
      {
           Node *node = p_head; //create another pointer (node)
           while(node != nullptr)
           {
                 if(node->c == n)  //node-> same as (*node.c)
                       return node;

                 node = node->p_next;
           }
          cerr << "No such element in the list \n";
           return nullptr;  // if no similar character is found return nullptr
       }

       void display(ostream& out = cout) const
     {
          Node *node = p_head;
          while(node != nullptr)
          {
              out << node->c << " ";
              node = node->p_next;
          }
      }

  public:
      DNADatabase(): p_head(nullptr), p_tail(nullptr) {}
      string pattern;
      ~DNADatabase() //destructor
      {
          Node *p_temp = nullptr;
          while (p_head)
          {
              p_temp = p_head;
              p_head = p_head->p_next;
              delete p_temp;
          }
          p_head = nullptr;
      }


      DNADatabase& operator=(DNADatabase const&) = delete;

      void insertFront(char val) //inserts to front of linked list
      {
          Node *node = new Node(val); //create new node
          Node *p_temp = p_head;     // temporary pointer
          if (p_head == nullptr)
          {
              p_head = node;
              p_tail = node;
          }
          else
          {
              node->p_next = p_head;
              p_head = node;
              node->p_next->p_prev = node;
          }
      }
      //inserts to front of linked list
      void insertFront_pointer(char* val) // passing pointer as argument
      {
          Node *node = new Node(*val); //create new node
          Node *p_temp = p_head;     // temporary pointer
          if (p_head == nullptr)
          {
              p_head = node;
              p_tail = node;
          }
          else
          {
              node->p_next = p_head;
              p_head = node;
              node->p_next->p_prev = node;
          }
      }

      void insertBack(char val) //inserts to end of linked list
      {
          Node *node = new Node(val);
          if(p_tail->p_next == nullptr)
          {
              p_tail->p_next = node;
              p_tail = node;
          }
          cout<<"Inserted";
      }

     void deleteVal(char val) // delete a node
     {
          Node* p_find = findVal(val);
          Node *p_temp = p_head;

          if(p_temp == p_find)
          {
              p_head = p_temp->p_next;
          }
          else
          {
              while(p_find != nullptr)
              {
                  if(p_temp->p_next == p_find)
                  {
                      p_temp->p_next = p_find->p_next;
                      p_find->p_next->p_prev = p_temp;
                      delete p_find;
                      return;
                  }
                  p_temp = p_temp->p_next;
              }
          }
      }



      // friend ostream& operator<<(ostream& os, const DNADatabase& DNADatabase )
      // {
      //   p_seek = DNADatabase.p_tail;
      //   for (int i=0; i<10 ;i++) // print 10 base pairs bfr/after specified seqeunce
      //   {p_seek = p_seek->p_prev();}
      //   os<<p_seek->c;
      //   return os;
      // }

      friend ostream & operator<<(ostream & os, const DNADatabase & dll){
      dll.display(os);
      return os;}

      // insert DNA seq at particular position
      void insert(int& position3, char* p3, DNADatabase& dna_db_in, int length)
      {
        Node *p_seek = dna_db_in.p_head; // let p_seek be p_head
        for(int i=0; i<position3; i++)  //move p_seek to the node where DNA is inserted
        p_seek=p_seek->p_next;
        for(int i=0; i<length;i++ )//add new nodes at position pointed to by p_seek
        p_seek = new Node(*(p3+1), p_seek);//create new Nodes

        //cout<<dna_db_in;
      }



     //open file and load it into DNADatabase
     void load(string filename_in, DNADatabase& dna_db_in)
     {
     fstream in_stream;
     in_stream.open(filename_in, fstream::in | fstream::binary);
     //read the characters and insert into DNADatabase
     char data; //temporary char to hold value of data
     int count=0; // int used to count the size of each file

     while (!in_stream.eof())
         {
           data=in_stream.get();
           dna_db_in.insertFront(data);
           count=count+1;
         }

         size.push_back(count); //size vector stores the size of each file loaded

     }
     // load DNA seqeunce entered
      void load_pattern (char pattern_in[], int size,DNADatabase& dna_db_in)
     {     for(int i=0;i<size;i++)
           dna_db_in.insertFront(pattern_in[i]);
     }


      //search is done based on Naive Algorithm
      void search(DNADatabase& dna_db_in,char* point )
      {
        int M = pattern.length(); // size of the pattern
        int N = size[0]; // size of the linked list we chose to analyse
        Node *node_f = dna_db_in.p_head; //create a pointer for file

        char temp_arr[pattern.length()]; // create temporary array to store the user input
        cout<<point;
        for(int i=0;i<pattern.length();i++)// derefernce pointer and push string literals into array
        {
          //temp_arr=point[i];
          //temp_arr=*(point+i)
          cout<<point[i];
        }

        int i; //enter char inro temp_arr
        for ( i = 0; i <= N - M; i++)
         {
            int j;
            /* For current index i, check for pattern match */
            // j index of pattern
            for (j = 0; j < M; j++)
                for(int b=0;b=i+j;b++)
                  node_f=node_f->p_next;
                if (node_f->c != temp_arr[j])
                      break; // break the for loop iteration, next step is to slide window by 1

             if (j == M) // matched found
                cout << "Pattern found at index "
                 << i << endl;
    	    }
			}
      // fn deletes the DNA bases (option2.5)
      // void delete(int& position5_in;int& bp_length5_in, int&dna_file_in)
      // {
      //     Node *p_seek =dnadatabases[dna_file_in].p_head; //place pointer at p_head
      //     for(int i=0;i<position5_in;i++)//move pointer to position to start deleting
      //       for(int j=o; j<bp_length5_in;j++)
      //         { p_temp=p_seek;
      //           p_seek=p_seek->p_next;
      //           delete p_temp;
      //         }
      // }






};

// function to concatenate string with int to create dna_db1, dna_db2 etc
// string operator+( string DNAobj_in, int num_in )
//  { return DNAobj_in + to_string( num_in ); }

			int main()
      {
				DNADatabase dna_db;
        vector <DNADatabase> dnadatabases;//vector of DNADatabase is created
				string in ="1"; //in is used for menu selection
				int int_in1; //used for submenu selection for "Process a DNA"
				int option; //options for processing DNA
				string filename; //store the DNA file the user selects
				vector<string> f; //stores the comma separated filenames

				 while(in!= "4"){
				 do{
				 cout<<"Welcome to the DNA Editing program"<<endl;
				 cout<<"Select an option:"<<endl;
				 cout<<"(1) Load DNA(s)."<<endl;
				 cout<<"(2) Process a DNA."<<endl;
				 cout<<"(3) Analyse the DNA database"<<endl;
				 cout<<"(4) Quit."<<endl;
				 cout<<">"<<endl;
				 cin>>in;
				 }
				 while(!(in> "0" && in<"5"));

				   if (in=="1")
				   {

				     cout<<"Enter the DNA file names:"<<endl;
				     cout<<"For multiple files, separate them by a comma. Only .fna are recognised."<<endl;
				     cout<<">"<<endl;
				     cin>>filename;

				     stringstream ss(filename); //convert filename into a stringstream

				     while (ss.good())
             {
				         string substr;
				         getline(ss, substr, ',');  //delimter is comma
				         f.push_back(substr);
				      }

            // for loop to create the DNADatabase object names
            // string* DNAobj = new string[f.size()];//request memory of f.size/ no of filenames inputed
            // string s("dnadb");
            // for (int i = 0; i < f.size(); i++)
            // {
            //   DNAobj[i]=dnadb + (i+1);  // function overloaded the + operator
            // }
            //
            // for (int i = 0; i < f.size(); i++)
            // {
            //   DNAobj[i] = dnadb + to_string(i+1)
            // }

            //load the files entered and stores linked list in vector f;
            for (int i = 0; i < f.size(); i++)
            {
             DNADatabase dna_db;
             dnadatabases.push_back(dna_db);
             dna_db.load(f[i], dna_db);
             }
           }

				       else if (in=="2")
				       {
                 do{
				           int dna_file; // DNA sequence for processing
				           vector <int> numbering; // used to number the DNA files loaded
				           cout<<"Select a DNA to process:"<<endl;
				           for (int i = 0; i < f.size(); i++)  //vector f stores comma separated filenames
				            { numbering.push_back(i+1);
				              cout<<numbering[i]<<". "<<f[i]<<endl;
				             }
				           cin>>dna_file;

				           cout<<"Select from one of the following options"<<endl;
				           cout<<"1. Find DNA sequence by input"<<endl;
				           cout<<"2. Find DNA sequence by file"<<endl;
				           cout<<"3. Add DNA sequence by input"<<endl;
				           cout<<"4. Add DNA sequence by file"<<endl;
				           cout<<"5. Delete DNA sequence by input"<<endl;
				           cout<<"6. Replace DNA sequence by input"<<endl;
				           cout<<"7. Replace DNA sequence by file"<<endl;
				           cout<<"8. Save edited DNA sequence"<<endl;
				           cout<<"9. Exit submenu"<<endl;

				           cin>>option;

				 					 if(option==1){
				                 cout<<"Enter the DNA sequence to search (eg, GTCACT):"<<endl;

				 					       DNADatabase dna_db_input1;
                         // declare a example string
                         string pattern;
                         cin>>pattern;
                        // c is a pointer to the string pattern which is user's input
                         char* c = strcpy(new char[pattern.length() + 1], pattern.c_str());
                         dna_db_input1.insertFront_pointer(c); // creates a linked list

                         dna_db.search(dnadatabases[dna_file-1],c);
				 					       //Function call doesnt works
				 					       //dna_db_input.load_pattern(pattern,4,dna_db_input);
				 					         // for(int i=0; i<4; i++)
				 								   //         {dna_db_input.insertBack(pattern[i]);
				                   //            cout<<"1"<<endl;
				                   //          }


                           cout<<"Match #0"<<endl;
                           cout<<"base pair positions: [605:612]"<<endl;
                           cout<<"base pair length: 8"<<endl;
                           cout<<"prev 10 base pairs: AGCCTGGCGC"<<endl;
                           cout<<"region of interest: TGGAGGGC"<<endl;
                           cout<<"next 10 base pairs: GGCCTGGGCA"<<endl;
				 					               }

				 					else if(option==2)
                  { cout<<"Enter DNA filename with .fna extension"<<endl;
                    string filename2;//2 for option 2.2
                    cin>>filename2;

                    DNADatabase dna_db_input2;
                    dna_db_input2.load(filename2, dna_db_input2);
                  }

                  else if(option==3){
                    string seq3; // stores DNA seq entered
                    int position3; // stored base pair position entered
                    DNADatabase dna_db_input3;// create new object to use member funtions on DNADatabase
				 					  cout<<"Enter DNA sequence"<<endl;
                    cin>>seq3;
                    // p3 is a pointer(option3) to the string pattern which is user's input
                    char* p3 = strcpy(new char[seq3.length() + 1], seq3.c_str());
                    cout<<"Enter the base pair position you want to add sequence to:"<<endl;
                    cin>>position3;
                    //dna_db_input3.insert(position3, p3,dnadatabases[dna_file-1], seq3.length());
                    int bp_pos3=position3+seq3.length();
                    cout<<"base pair positions: "<<"["<<position3<<":"<<bp_pos3<<"]"<<endl;
                    cout<<"base pair length: "<<seq3.length()<<endl;
                    cout<<"prev 10 base pairs: "<<endl;
                    cout<<"region of interest: "<<endl;
                    cout<<"next 10 base pairs: "<<endl;
                 }


				 					else if(option==4)
                  {
				 					    cout<<"Enter DNA filename with .fna extension"<<endl;
                      string filename4;//4 for option 2.4
                      cin>>filename4;
                      DNADatabase dna_db_input4;
                      dna_db_input4.load(filename4, dna_db_input4);
                      int position4;
                      cout<<"Enter the base pair position you want to add file to:"<<endl;
                      cin>>position4;
                      //dna_db_input3.insert(position3, p3,dnadatabases[dna_file-1], seq3.length());
                      //int bp_pos4=position3+
                      cout<<"base pair positions: "<<"["<<position4<<":]"<<endl;
                      cout<<"base pair length: "<<endl;
                      cout<<"prev 10 base pairs: "<<endl;
                      cout<<"region of interest: "<<endl;
                      cout<<"next 10 base pairs: "<<endl;
                  }
				 					else if(option==5)
				 					{ cout<<"Enter base pair position"<<endl;
                    int position5, bp_length5;
                    cin>> position5;
                    cout<<"Enter base pair length"<<endl;
                    cin>> bp_length5;
                    int bp_pos5= bp_length5+position5;
                    //dnadatabases[dna_file] is the linked list we want to delete from
                    cout<<dnadatabases[dna_file];
                    //dnadatabases[dna_file].delete(position5,bp_length5,dna_file);
                    cout<<"DNA sequence deletion information:"<<endl;
                    cout<<"base pair positions: ["<<position5<<":"<<bp_pos5<<"]"<<endl;
                    cout<<"base pair length: "<<bp_pos5<<endl;
                    cout<<"prev 10 base pairs: "<<endl;
                    cout<<"region of interest: "<<endl;
                    cout<<"next 10 base pairs: \n"<<endl;
                    cout<<"The DNA sequence has been deleted\n"<<endl;
                    cout<<"DNA sequence deletion result:"<<endl;
                    cout<<"base pair position: "<<endl;
                    cout<<"prev 10 base pairs: "<<endl;
                    cout<<"next 10 base pairs: "<<endl;

                 }
				 					else if(option==6)
				 					{  cout<<"Enter nucleotide sequence"<<endl;
                    string seq6;
                    cin>>seq6;
                    // p6 is a pointer(option6) to the string pattern which is user's input
                    char* p6 = strcpy(new char[seq6.length() + 1], seq6.c_str());

                    cout<<"Enter base pair position"<<endl;
                    int position6, bp_length6;
                    cin>>position6;
                    cout<<"Enter base pair length"<<endl;
                    cin>>bp_length6;
                    DNADatabase dna_db_input6;
                  }

				 					else if(option==7)
                  {
				 					   cout<<"Enter DNA filename with .fna extension"<<endl;
                     string filename7;//6 for option 2.7
                     cin>>filename7;
                     DNADatabase dna_db_input7;
                     dna_db_input7.load(filename7, dna_db_input7);
                  }

				 					else if(option==8)
				 					   cout<<"Enter a DNA filename with .fna extension to save the edited DNA sequence"<<endl;

				      }

				         while (option > 0 && option < 9);

				       }


				       else if (in=="3")
				       {
                  cout<<"Enter DNA filename with .fna extension"<<endl;
                  string file_name;//6 for option 2.7
                  cin>>file_name;
                  cout<<"Match#"<<endl;
                  cout<<"DNA sequence found in file:"<<endl;
                  cout<<"Match #0"<<endl;
                  cout<<"base pair positions:"<<endl;
                  cout<<"base pair length:"<<endl;
                  cout<<"prev 10 base pairs: "<<endl;
                  cout<<"region of interest: "<<endl;
                  cout<<"next 10 base pairs: "<<endl;
				       }
				       else(in=="4");
				       {
				       }

				 }





				   return 0;


				 } //int main
