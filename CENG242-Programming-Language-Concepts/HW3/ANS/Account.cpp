#include "Account.h"

using namespace std;




 /**
     * Empty constructor
     * give the id as -1
     * give nullptr for pointers
     */
    Account :: Account(){
    	this->_id = -1;
    	this->_activity = nullptr;
    	this->_monthly_activity_frequency = nullptr;


    }
    /**
     * Constructor
     * 
     * 
     * Note: The given activity array will have 12 Transaction* 
     * Each of these Transaction* will represent a month from the 2019
     * Basicaly activity[0] will represent January
     *          activity[11] will represent February
     *          activity[11] will represent March
     *                      ...
     *          activity[10] will represent November
     *          activity[11] will represent December
     * activity[0] will only contain Transactions happened in January
     * However, be careful that Transactions inside of activity[i] will not be in sorted order
     * For Example: We are certain that activity[0] is containing Transactions happened in January 2019
     * But we are not sure which of them happened first.
     * I strongly suggest you to use a sorting algorithm while storing these Transaction to your object.
     * (Sorting by the date, So that you can directly use them in stream overload)
     * (You can use bubble sort)
     * 
     * @param id id of this Account
     * @param activity 2d Transaction array first layers lenght is 12 for each month
     * @param monthly_activity_frequency how many transactions made in each month
    */
    Account ::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
    	Transaction temp;
    	int numLength;
    	int i, j, flag,k = 1;
    	this-> _id = id;
		this-> _activity = new Transaction* [12] ;    
		this-> _monthly_activity_frequency = new  int [12];

    	
    	for(int month_val = 0; month_val < 12 ; month_val++){
    		
    		this-> _activity[month_val] = new Transaction [monthly_activity_frequency[month_val]];
    		this-> _monthly_activity_frequency[month_val] = monthly_activity_frequency[month_val];
    		for (int freq_val = 0; freq_val < monthly_activity_frequency[month_val]; freq_val ++){
    			this-> _activity[month_val][freq_val] = activity[month_val][freq_val];		// burda ocağın 1. işlemi 2 ...10 işlemine ne atıcam transcation mı?

    		}
    	}

    	
    	for(k=0;k<12;k++){
 			i, j, flag = 1;
 			numLength = this->_monthly_activity_frequency[k];
	      for(i = 1; (i <= numLength) && flag; i++)
	     {
	          flag = 0;
	          for (j=0; j < (numLength -1); j++)
	         {
	               if (this->_activity[k][j+1] < this->_activity[k][j])      
	              { 
	                    temp = this->_activity[k][j];             
	                    this->_activity[k][j] = this->_activity[k][j+1];
	                    this->_activity[k][j+1] = temp;
	                    flag = 1;               
	               }
	          }
	     }
	    }


	

    }
    

    /**
     * Destructor
     * 
     * Do not forget to free the space you have created(This assignment does not use smart pointers)
     */
    Account ::~Account(){  //activty null mı değil mi kontrol edip null değilse delete ac
    	for(int month_val=0 ; month_val<12 ; month_val++){
			if(_activity != nullptr && _activity[month_val] != nullptr){
				delete [] _activity[month_val];
			}
		}
		if(_activity != nullptr){
			delete [] _activity;
		}
    	if(_monthly_activity_frequency != nullptr){
			delete [] _monthly_activity_frequency;
    	}

    }

    /**
     * Copy constructor(Deep copy)
     * 
     * @param other The Account to be copied
     */
    Account :: Account(const Account& rhs){
    	int len;
    	this-> _id = rhs._id;
		this-> _activity = new Transaction* [12] ;    
		this-> _monthly_activity_frequency = new  int [12];  

		for(int month_val = 0; month_val < 12 ; month_val++){
    		len = rhs._monthly_activity_frequency[month_val];
    		this-> _activity[month_val] = new Transaction [len];
    		this-> _monthly_activity_frequency[month_val] = rhs._monthly_activity_frequency[month_val];
    		for (int freq_val = 0; freq_val < _monthly_activity_frequency[month_val]; freq_val ++){
    			this-> _activity[month_val][freq_val] = rhs._activity[month_val][freq_val];		

    		}
    	}
    }


    /**
     * Copy constructor(Deep copy)
     * 
     * This copy constructors takes two time_t elements
     * Transactions of the old Account will be copied to new Account 
     * if and only if they are between these given dates
     * Given dates will not be included.
     * 
     * @param rhs The Account to be copied
     * @param start_date Starting date for transaction to be copied.
     * @param end_date Ending date for transactions to be copied.
     */
    Account ::Account(const Account& rhs, time_t start_date, time_t end_date){

    	int count,k,len;
    	Transaction* temp;
    	count = 0;
    	this-> _id = rhs._id;
		this-> _activity = new Transaction* [12] ;    
		this-> _monthly_activity_frequency = new  int [12];  

		if(rhs._activity != nullptr){	
			for(int month_val = 0; month_val < 12 ; month_val++){
	    		len = rhs._monthly_activity_frequency[month_val];
	    		this-> _activity[month_val] = new Transaction [len];
	    		this-> _monthly_activity_frequency[month_val] = rhs._monthly_activity_frequency[month_val];
	    		for (int freq_val = 0; freq_val < _monthly_activity_frequency[month_val]; freq_val ++){
	    			this-> _activity[month_val][freq_val] = rhs._activity[month_val][freq_val];		

	    		}
	    	}
	    }

    	for(int month_val = 0; month_val < 12 ; month_val++){
    		count = 0;
    		for (int freq_val = 0; freq_val < _monthly_activity_frequency[month_val]; freq_val ++){
    			if(this-> _activity[month_val][freq_val]>start_date&&this-> _activity[month_val][freq_val]<end_date){
    				count++;
    			}		
    		}

    		temp = new Transaction [count];
    		k=0;
    		for (int freq_val = 0; freq_val < _monthly_activity_frequency[month_val]; freq_val ++){
    			if(this-> _activity[month_val][freq_val]>start_date&&this-> _activity[month_val][freq_val]<end_date){
    				temp[k] = this->_activity[month_val][freq_val];
    				k++;	
    			}	

    		}
    		this->_activity[month_val] = temp;
    		delete [] temp;
    		this->_monthly_activity_frequency[month_val] = count;
    	}






	}
		
    

    
    
    /**
     * Move constructor
     * 
     * @param rhs Account which you will move the resources from
     */
    Account ::Account(Account&& rhs){

    	this-> _id = rhs._id;
		this-> _activity = rhs._activity ;    
		rhs._activity = nullptr;
		this-> _monthly_activity_frequency = rhs._monthly_activity_frequency;  
		rhs._monthly_activity_frequency = nullptr;
		
    }

    /**
     * Move assignment operator
     * 
     * @param rhs Account which you will move the resources from
     * @return this account 
     */
    Account& Account :: operator=(Account&& rhs){
    	this-> _id = rhs._id;
		this-> _activity = move(rhs._activity) ;    
		rhs._activity = nullptr;
		this-> _monthly_activity_frequency = rhs._monthly_activity_frequency;  
		rhs._monthly_activity_frequency = nullptr;
return *this ;
    }

    /**
     * Assignment operator
     * deep copy
     * 
     * @param rhs Account to assign
     * @return this account 
     */
    Account& Account :: operator=(const Account& rhs){
return *this ;

    }
    /**
     * Equality comparison overload
     * 
     * This operator checks only id of the Account
     * 
     * @param rhs The Account to compare
     * @return returns true if both ids are same false othervise
     */
    
    bool Account :: operator==(const Account& rhs) const{
    	return true;

    }
    /**
     * Equality comparison overload
     * 
     * This operator checks only id of the Account
     * 
     * @param id to compare
     * @return returns true if both ids are same false othervise
     */
    bool  Account :: operator==(int id) const{
    	return true;

    }
    

    /**
     * sum and equal operator
     * Add Transactions of two Accounts
     * You have to add transactions in correct places in your _activity array
     * Note: Remember that _activity[0] is always January and _activity[11] is always December
     * (This information also holds for every other month)
     * 
     * You can have Transactions with the same date
     * 
     * @param rhs Account which take new Transactions from
     * @return this Account after adding new Transactions
     */
    Account& Account :: operator+=(const Account& rhs){
    	return *this ;

    }

    /**
     * How much money Account has(Sum of Transaction amounts)
     *
     * 
     * @return total amount of the money of the account
     */
    double Account :: balance(){
    	double sum;
    	int counter, counterr;
    	counter = counterr = 0;
    	sum = 0;
    	if(this->_activity == nullptr || this->_monthly_activity_frequency == nullptr){
    		return -1;
    	}
    		while(counter<12){
	    		while(counterr < this->_monthly_activity_frequency[counter] ){
	    			sum = this->_activity[counter][counterr] + sum;
	    			counterr++;
	    		}
	    		counterr = 0;
	    		

	    		counter++;
	    	}
	    return sum;

    }

    /**
     * How much money Account has at the end of given date
     * 
     * Given date will not be included.
     * @param end_date You will count the amounts until this given date(not inclusive)
     * @return Total amount the Account has until given date
     */


    double Account :: balance(time_t end_date){
    	double sum;
    	int counter, counterr;
    	counter = counterr = 0;
    	sum = 0;
    	if(this->_activity == nullptr || this->_monthly_activity_frequency == nullptr){
    		return -1;
    	}
    		while(counter<12){
	    		while(counterr < this->_monthly_activity_frequency[counter] ){
	    			if(this->_activity[counter][counterr] < end_date){
	    				sum = this->_activity[counter][counterr] + sum;

	    			}
	    			counterr++;
	    		}
	    		counterr = 0;
	    		

	    		counter++;
	    	}
	   	return sum;

    }




    /**
     * How much money Account between given dates
     * Given dates will not be included.
     * 
     * @param end_date You will count the amounts between given dates(not inclusive)
     * @return Total amount the Account has between given dates
     * You will only count a Transaction amount if and only if it occured between given dates
     */
    double Account :: balance(time_t start_date, time_t end_date){
    	double sum;
    	int counter, counterr;
    	counter = counterr = 0;
    	sum = 0;
    	if(this->_activity == nullptr || this->_monthly_activity_frequency == nullptr){
    		return -1;
    	}
    		while(counter<12){
	    		while(counterr < this->_monthly_activity_frequency[counter] ){
	    			if(_activity[counter][counterr] > start_date && _activity[counter][counterr] < end_date){
	    				sum = this->_activity[counter][counterr] + sum;

	    			}
	    			counterr++;
	    		}
	    		counterr = 0;
	    		

	    		counter++;
	    	}
	   	return sum;

    }





    /**
     * Stream overload.
     * 
     * 
     * 
     * What to stream
     * Id of the user
     * Earliest Transaction amount"tab"-"tab"hour:minute:second-day/month/year(in localtime)
     * Second earliest Transaction amount"tab"-"tab"hour:minute:second-day/month/year(in localtime)
     * ...
     * Latest Transaction amount"tab-tab"hour:minute:second-day/month/year(in localtime)
     * 
     * Note: _activity array will only contain dates from January 2019 to December 2019
     * Note: Transactions should be in order by date
     * Note: either of _monthly_activity_frequency or _activity is nullptr
     * you will just stream
     * -1
     * @param os Stream to be used.
     * @param Account to be streamed.
     * @return the current Stream
     */
    
    ostream& operator<<(std::ostream& os, const Account& account){
    	int counter =  0;
    	int counterr = 0 ;


    	if(account._monthly_activity_frequency == nullptr || account._activity == nullptr)
    	{
    		os<<-1;
    	}
    	else{
	    	os << account._id<<endl;
	    	while(counter<12){
	    		while(counterr < account._monthly_activity_frequency[counter] ){


	    			os << account._activity[counter][counterr] ;
	    			counterr++;
	    		}
	    		counterr = 0;
	    		

	    		counter++;
	    	}

    	}

    	return os;
    }
