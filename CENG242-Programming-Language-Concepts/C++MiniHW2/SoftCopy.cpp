#include "SoftCopy.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
THE CONSTRUCTOR and DESTRUCTOR ARE ALREADY IMPLEMENTED.
START YOUR IMPLEMENTATIONS BELOW THOSE. */


// DONE
SoftCopy::SoftCopy(int ISBN, double price, int startPage, int endPage) : Book(ISBN, price) {
	this->startPage = startPage;
	this->endPage = endPage;
	this->numberOfPages = (endPage - startPage) + 1;
	this->firstHalf = NULL;
	this->secondHalf = NULL;
	this->pageContent = "";
}


// DONE
SoftCopy::~SoftCopy() {
	if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;
}

//    Implemented
SoftCopy::SoftCopy(const SoftCopy& parm_soft){
    ISBN = parm_soft.ISBN;
    price = parm_soft.price;
    this->startPage = parm_soft.startPage;
	this->endPage = parm_soft.endPage;
	this->numberOfPages = parm_soft.numberOfPages;
	this->pageContent = parm_soft.pageContent;
	next =NULL;
	if (parm_soft.firstHalf==nullptr){
	    firstHalf = NULL;
	}
	else{
	    firstHalf = new SoftCopy (*parm_soft.firstHalf);
	}
	if (parm_soft.secondHalf==nullptr){
	    secondHalf = NULL;
	}
	else{
	    secondHalf = new SoftCopy (*parm_soft.secondHalf);
	}
	
    
}
//    Implemented
SoftCopy& SoftCopy:: operator=(const SoftCopy& parm_opr ){
    ISBN = parm_opr.ISBN;
    price = parm_opr.price;
    this->startPage = parm_opr.startPage;
	this->endPage = parm_opr.endPage;
	this->numberOfPages = parm_opr.numberOfPages;
	this->pageContent = parm_opr.pageContent;
	next =NULL;
	delete firstHalf;
	delete secondHalf;
	if (parm_opr.firstHalf==nullptr){
	    firstHalf = NULL;
	}
	else{
	    firstHalf = new SoftCopy (*parm_opr.firstHalf);
	}
	if (parm_opr.secondHalf==nullptr){
	    secondHalf = NULL;
	}
	else{
	    secondHalf = new SoftCopy (*parm_opr.secondHalf);
	}
	
}


SoftCopy& SoftCopy:: operator+(const SoftCopy&) const{
    return *(new SoftCopy (ISBN,price,14,209));
    
}

//    Implemented
 Book*  SoftCopy:: Clone() const{
    return new SoftCopy (*this);
}

//    Implemented
void SoftCopy::  Discount(){
    this->price *= 75/100.0;
}

//    Implemented
void SoftCopy::  UploadPage(string parm_cont, int parm_pagno){
    if (this->startPage == endPage && endPage==parm_pagno ){
    this->pageContent = parm_cont;    
    }
    else{
        int temp_endpage = (startPage + ((endPage - startPage)/2));
        int temp_startpage = (endPage - ((endPage - startPage)/2));
        if(parm_pagno <= temp_endpage) {
            if(firstHalf == NULL){
                firstHalf = new SoftCopy ( ISBN,  price,  startPage,  temp_endpage);
                firstHalf-> UploadPage( parm_cont,  parm_pagno);
            }
            else{
            firstHalf-> UploadPage( parm_cont,  parm_pagno);
            }
            
        }else{
             if(secondHalf == NULL){
                secondHalf = new SoftCopy ( ISBN,  price, temp_startpage , endPage  );
                secondHalf-> UploadPage( parm_cont,  parm_pagno);
            }
            else{
            secondHalf-> UploadPage( parm_cont,  parm_pagno);
            }           
        }
    
    
    }
}

string SoftCopy::  Display(int from, int to) const{
   /* string all_cont ="";
    if (this->startPage == endPage  ){
    return pageContent ;    
    }
    else{
        int dis_endpage = (from + ((to - from)/2));
        int dis_startpage = (to - ((to - from)/2));
        if(from <= dis_endpage) {
            
            if(firstHalf == NULL){
                return "";
            }
            else
            {
            
            all_cont += firstHalf-> Display(from,  dis_endpage);
            }
            
        }else{
             if(secondHalf == NULL){
                return "";
            }
            else
            {
            
            all_cont += secondHalf-> Display( dis_startpage,  to);
            }           
        }
    return all_cont;
    
}
//return NULL;
*/
/*if (this->startPage == endPage  ){
        if(to == this->endPage && secondHalf == NULL)
        return pageContent  ;
        else
        return pageContent + "\n";
    }
    else{
        if(this->firstHalf == NULL){
            if(this->secondHalf == NULL){
                return "";
            }
            else{
                return this->secondHalf->Display(from, to);
            }
        }
        else if(this->secondHalf == NULL){
            return this->firstHalf->Display(from, to);
        }
        else {
            return this->firstHalf->Display(from, to) + this->secondHalf->Display(from, to);
        }

    }*/
return NULL;
}



