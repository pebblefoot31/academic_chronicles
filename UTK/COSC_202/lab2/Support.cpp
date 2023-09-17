#include "Support.h"
#include <iostream>
#include <iomanip>

// Add location and list member function code here.

bool location::operator<(const location& l) const {
    if (state < l.state) 
        return true;
    else if (state == l.state && city < l.city)
            return true;
    else
        return false;
}    

bool location::operator==(const std::string& l) const { 
    if (state == l || city == l || geocode == l) 
        return true;
    else
        return false;
}

bool location::operator==(const location& l) const {
    if (geocode == l.geocode || city == l.city)
        return true;
    else return false; 
}

list::node::node(const location &n_station) {

    station = n_station;
    
    total_precip = new float[12];
    max_precip = new float[12]; 
    min_precip = new float[12];
    total_temp = new int[12];
    max_temp = new int[12];
    min_temp = new int[12];
    N = new int[12];

    for(int i=0;i<12;i++) {

        total_precip[i] = 0;
        max_precip[i] = 0;
        min_precip[i] = 100;
        total_temp[i] = 0;
        max_temp[i] = 0;
        min_temp[i] = 100;
        N[i] = 0; 
    }
}

list::node::~node() {

    delete [] total_precip;
    delete [] max_precip;
    delete [] min_precip;
    delete [] total_temp;
    delete [] max_temp;
    delete [] min_temp;
}

list::list() {
   head = nullptr;
}


list::~list() {
    while (head != nullptr) {
        node* currNode = head;
        head = currNode->next;
        delete currNode;
    }
}

void list::insert(const location& l, const data& d) {

    node* tmp = nullptr;
    node* myNode = nullptr;
    bool found = false;

    if (head == nullptr) { 
        head = new node(l); 

        head->N[d.month-1]++;
        head->total_precip[d.month-1] += d.precip;
        if (d.precip >= head->max_precip[d.month-1])
            head->max_precip[d.month-1] = d.precip;
        if (d.precip <= head->min_precip[d.month-1])
            head->min_precip[d.month-1] = d.precip;
        if (d.temp >=  head->max_temp[d.month-1])
            head->max_temp[d.month-1] = d.temp;
        if (d.temp <= head->min_temp[d.month-1])
            head->min_temp[d.month-1] = d.temp;
        head->total_temp[d.month-1] += d.temp; 

        head->next = nullptr;
    } else if(head->station.geocode == l.geocode){
	    found=true;
	    myNode=head;
    }else{
        tmp = head;
        //while (tmp->next != nullptr) {
        while (tmp != nullptr) {
		    if(tmp->station.geocode == l.geocode){
			    found=true;
			    myNode=tmp;
			    break;
		    }
        	tmp = tmp->next;
        }
        
	if(found==false){
		tmp = head;
		while(tmp->next != nullptr){
		       	tmp=tmp->next;
		}
        myNode = new node(l);
		tmp->next = myNode;
		myNode->next = nullptr;
	 }
    }

    if(myNode != nullptr){
        myNode->N[d.month-1]++;
        myNode->total_precip[d.month-1] += d.precip;
        if (d.precip >= myNode->max_precip[d.month-1])
            myNode->max_precip[d.month-1] = d.precip;
        if (d.precip <= myNode->min_precip[d.month-1])
            myNode->min_precip[d.month-1] = d.precip;
        if (d.temp >=  myNode->max_temp[d.month-1])
            myNode->max_temp[d.month-1] = d.temp;
        if (d.temp <= myNode->min_temp[d.month-1])
            myNode->min_temp[d.month-1] = d.temp;
        myNode->total_temp[d.month-1] += d.temp; 
    }
}

void list::print(const char * c) { //calls print_data and print_station (global print function)

    node* tmp = head;
    while (tmp->next != nullptr) {
        tmp->print_station();
        tmp->print_data();
        tmp = tmp->next;
    }
}


void list::node::print_station() {
    for (int i =0; i <42; i++)
        std::cout << "-";
    std::cout << std::endl;
    std::cout << station.city << ", " << station.state << " (" << station.geocode << ")" << std::endl;
    for (int i =0; i <42; i++)
         std::cout << "-";
     std::cout << std::endl;
}
 
void list::node::print_data() {
    std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i =0; i <12; i++)
        //std::cout << months[i] << ":  " << total_precip[i] << " " << total_precip[i]/N[i] << " " << max_precip[i] << " " << min_precip[i] << " :  " << total_temp[i]/N[i] << " " << max_temp[i] << "  "     << min_temp[i] << std::endl; // fix the formatting, especially spaces
        //std::cout << months[i] << ":  " << total_precip[i] << " " << total_precip[i]/N[i] << " " << max_precip[i] << " " << min_precip[i] << " :  " << (float)total_temp[i]/N[i] << " " << max_temp[i] << "  "  << min_temp[i] << std::endl; // fix the formatting, especially spaces

    std::cout << months[i] << ": " << std::fixed << std::setprecision(2) << std::setw(5) << total_precip[i] << " " << std::setw(5) << total_precip[i]/N[i] << " " << std::setw(5) << max_precip[i] << " " << std::setw(5) << min_precip[i] << " :  " << total_temp[i]/N[i] << "  " << max_temp[i] << "  " << min_temp[i] << std::endl; 
}

