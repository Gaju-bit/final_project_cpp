#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

class FinalProject
{
	public:
	int id;
	/**creating the data structures to store the values
     *intializing global variable
     * */
    string destinationICAOCode,sourceICAOCode, destinationIATACode, sourceIATACode, sourceAirportID, destinationAirportID;
	string destination_country,destination_city, source_country,source_city;
    vector<vector<string>> airportinfo;
	vector<string> row;
	string line, word, line2,word2;
	vector<vector<string>>destination_airport_details;
	vector<vector<string>>source_airport_details;

	vector<vector<string>> routeinfo;
	vector<vector<string>> routeFromSourceToDestination;
	vector<string> row2;
	

    void setCurrentRoute(){
		/**getting inputs from the user
     *start country and city
     * destination country and city
     * */
        cout<<"Enter the start country: ";
        cin>>source_country;

        cout<<"\nEnter the start city: ";
        cin>>source_city;

        cout<<"\nEnter the Destination country: ";
        cin>>destination_country;

        cout<<"\nEnter the Destination city: ";
        cin>>destination_city;
        
    }




	/**getting data from the airport.csv file
     * then using the inputs from the user for start and destination with and statement
     * got the airports from the source country and destination country
     * also got the number of stops from the route file and using a four loop i got the total number of stops for all the route
     * */
	void readfile(){
		//calling the setCurrentRoute function to take inputs
		setCurrentRoute();

		// opening and readinf the airports csv file and then using the inputs from the setCurrentRoute function to
		// get the source and destination airports respectively
		fstream file ("airports.csv");
		if(file.is_open()){
		while(getline(file, line)){
			row.clear();
		
			stringstream str(line);
		
			while(getline(str, word, ','))
			row.push_back(word);
			airportinfo.push_back(row);
		}
		}else
		cout<<"Could not open the file\n";

		//comparing the souce and destination from the user inputs with the airports information from the scv file
		//if they match we append it to a vector for the respectective airpoorts that is souce and destinatrion airports
		for (int i = 0; i < airportinfo.size(); i++)
		{
			if (source_country.compare(airportinfo[i][3]) ==0 && source_city.compare(airportinfo[i][2]) == 0)
			{
				
				source_airport_details.push_back(airportinfo[i]);
				
			}
			
		}
		for (int a = 0; a < source_airport_details.size(); a++)
		{
			for (int j = 0; j <source_airport_details[a].size(); j++)
			{
				cout << source_airport_details[a][j] << " ";
			}
			cout << "\n";
		}


		
		for (int i = 0; i < airportinfo.size(); i++)
		{
			if (destination_country.compare(airportinfo[i][3]) ==0 && destination_city.compare(airportinfo[i][2]) == 0)
			{
				destination_airport_details.push_back(airportinfo[i]);
				
			}
			
		}
		
		//Printing out the source and destination airports to comnfirm is if the algorithm got the actual data
		for (int a = 0; a < destination_airport_details.size(); a++)
		{
			for (int j = 0; j <destination_airport_details[a].size(); j++)
			{
				
				cout << destination_airport_details[a][j] << " ";
			}
			cout << "\n";
		}
		
	}

	/**create setters  the start route of the user
     *using the start and destination from the airport class
     * getting data from the route.csv file
     * then using the airport ID for start and destination with and statement
     * and the start and destination airport ID to compare with the start and destination Airport ID from the route file
     * i then got the airports route from start airport to the destination Airport
     * also got the number of stops from the route file and using a four loop i got the total number of stops for all the route
     * */

	void airlines()
	{

		//this function reads the route csv file to find the all routes that lead from the source to destination city
		
		//reading the routes.scv file
		readfile();
		fstream file2("routes.csv");
		if (file2.is_open())
		{
			while (getline(file2, line2))
			{
				row2.clear();

				stringstream str(line2);

				while (getline(str, word2, ','))
					row2.push_back(word2);
				routeinfo.push_back(row2);
			}
		}
		else{
			cout << "Could not open the file\n";
		}


		//comparing the destination and source airport id with that of the route source airport and destination airport Id and if the match
		//it indicated that there is a route between the two end point

		//with this we use the size of the vector we stored the routes in to indcated the number of flights from the source to destination
		//also adding all the stops from the routes in all routes avaliable gave us the total stops
		for (int i = 0; i < destination_airport_details.size(); i++)
		{
			for (int k = 0; k < source_airport_details.size() ; k++)
			{
				for (int j = 0; j < routeinfo[i].size(); j++)
				{
					if (source_airport_details[k][0].compare(routeinfo[j][3]) == 0 && destination_airport_details[i][0].compare(routeinfo[j][5]) == 0)
					{
						routeFromSourceToDestination.push_back(routeinfo[j]);
					}
					
				}
			}
			
			
			
		}
		//creating a txt file to stored the final
		ofstream MyFile("finaloutput.txt");
		int count = 1;
		int total_flight,total_stops =0;
		for (int i = 0; i < routeFromSourceToDestination.size(); i++)
		{
			total_stops = total_stops + stoi(routeFromSourceToDestination[i][7]);
			total_flight = routeFromSourceToDestination.size();
			cout <<count<<" "<< routeFromSourceToDestination[i][0] << " from " << routeFromSourceToDestination[i][2]<<" to " <<routeFromSourceToDestination[i][4]<<" "<<routeFromSourceToDestination[i][7]<<" "<<"stops";
			MyFile <<count<<" "<< routeFromSourceToDestination[i][0] << " from " << routeFromSourceToDestination[i][2]<<" to " <<routeFromSourceToDestination[i][4]<<" "<<routeFromSourceToDestination[i][7]<<" "<<"stops\n";
			cout << "\n";
			cout<<"Total flights: "<<total_flight;
			cout << "\n";
			cout << "Total additional stops: "<<total_stops;

			//writing the inputs to the txt file
			MyFile<<"\nTotal flights: "<<total_flight;
			MyFile << "\nTotal additional stops: "<<total_stops;
			count++;

		}
			

		// if (destination_airport_details.size() > source_airport_details.size())
		// {
		// 	for (int c = 0; c < destination_airport_details.size(); c++)
		// 	{
		// 		for (int d = 0; d < routeinfo.size(); d++)
		// 		{
		// 			if (source_airport_details[c][0].compare(routeinfo[d][3]) == 0 && destination_airport_details[c][0].compare(routeinfo[d][5]) == 0)
		// 			{
		// 				routeFromSourceToDestination.push_back(routeinfo[d]);
		// 				cout<<routeFromSourceToDestination[0][0];
		// 			}
		// 		}
		// 	}
		// }
		// else
		// {
		// 	for (int c = 0; c < source_airport_details.size(); c++)
		// 	{
		// 		for (int d = 0; d < routeinfo.size(); d++)
		// 		{
		// 			if (source_airport_details[c][0].compare(routeinfo[d][3]) == 0 && destination_airport_details[c][0].compare(routeinfo[d][5]) == 0)
		// 			{
		// 				routeFromSourceToDestination.push_back(routeinfo[d]);
		// 				cout<<routeFromSourceToDestination[0][0];
		// 			}
		// 		}
		// 	}
		// }
		 
		

	}

};
int main() {
	
	FinalProject Angel;
	// obj1.readfile();
	Angel.airlines();
	return 0;
}



