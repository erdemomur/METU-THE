package ceng.ceng351.carpoolingdb;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class CarPoolingSystem implements ICarPoolingSystem {

    private static String url = "jdbc:h2:mem:carpoolingdb;DB_CLOSE_DELAY=-1"; // In-memory database
    private static String user = "sa";          // H2 default username
    private static String password = "";        // H2 default password

    private Connection connection;

    public void initialize(Connection connection) {
        this.connection = connection;
    }

    //Given: getAllDrivers()
    //Testing 5.16: All Drivers after Updating the Ratings
    @Override
    public Driver[] getAllDrivers() {
        List<Driver> drivers = new ArrayList<>();
        
        //uncomment following code slice
        /*String query = "SELECT PIN, rating FROM Drivers ORDER BY PIN ASC;";

        try {
            PreparedStatement ps = this.connection.prepareStatement(query);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                int PIN = rs.getInt("PIN");
                double rating = rs.getDouble("rating");

                // Create a Driver object with only PIN and rating
                Driver driver = new Driver(PIN, rating);
                drivers.add(driver);
            }
            rs.close();
            ps.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        */
        
        return drivers.toArray(new Driver[0]); 
    }

    
    //5.1 Task 1 Create tables
    @Override
    public int createTables() {
        int tableCount = 0;

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        return tableCount;
    }


    //5.17 Task 17 Drop tables
    @Override
    public int dropTables() {
        int tableCount = 0;
        
        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        return tableCount;
    }
    
    
    //5.2 Task 2 Insert Participants
    @Override
    public int insertParticipants(Participant[] participants) {
        int rowsInserted = 0;

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
        
        return rowsInserted;
    }

    
    //5.2 Task 2 Insert Passengers
    @Override
    public int insertPassengers(Passenger[] passengers) {
        int rowsInserted = 0;

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
        
        return rowsInserted;
    }


    //5.2 Task 2 Insert Drivers
    @Override
    public int insertDrivers(Driver[] drivers) {
        int rowsInserted = 0;

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
        
        return rowsInserted;
    }

    
    //5.2 Task 2 Insert Cars
    @Override
    public int insertCars(Car[] cars) {
        int rowsInserted = 0;
        
        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        return rowsInserted;
    }


    //5.2 Task 2 Insert Trips
    @Override
    public int insertTrips(Trip[] trips) {
        int rowsInserted = 0;

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
        
        return rowsInserted;
    }

    //5.2 Task 2 Insert Bookings
    @Override
    public int insertBookings(Booking[] bookings) {
        int rowsInserted = 0;
        
        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        return rowsInserted;
    }

    
    //5.3 Task 3 Find all participants who are recorded as both drivers and passengers
    @Override
    public Participant[] getBothPassengersAndDrivers() {
    	
        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
    	return new Participant[0];
    }

 
    //5.4 Task 4 Find the PINs, names, ages, and ratings of drivers who do not own any cars
    @Override
    public QueryResult.DriverPINNameAgeRating[] getDriversWithNoCars() {
    	
        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
    	return new QueryResult.DriverPINNameAgeRating[0];
    }
 
    
    //5.5 Task 5 Delete Drivers who do not own any cars
    @Override
    public int deleteDriversWithNoCars() {
        int rowsDeleted = 0;

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
        
        return rowsDeleted;  
    }

    
    //5.6 Task 6 Find all cars that are not taken part in any trips
    @Override
    public Car[] getCarsWithNoTrips() {
    	
        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Car[0];
    }
    
    
    //5.7 Task 7 Find all passengers who didn't book any trips
    @Override
    public Passenger[] getPassengersWithNoBooks() {
    	
        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Passenger[0];
    }


    //5.8 Task 8 Find all trips that depart from the specified city to specified destination city on specific date
    @Override
    public Trip[] getTripsFromToCitiesOnSpecificDate(String departure, String destination, String date) {
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Trip[0]; 
    }


    //5.9 Task 9 Find the PINs, names, ages, and membership_status of passengers who have bookings on all trips destined at a particular city
    @Override
    public QueryResult.PassengerPINNameAgeMembershipStatus[] getPassengersWithBookingsToAllTripsForCity(String city) {
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.PassengerPINNameAgeMembershipStatus[0];
    }

    
    //5.10 Task 10 For a given driver PIN, find the CarIDs that the driver owns and were booked at most twice.    
    @Override
    public Integer[] getDriverCarsWithAtMost2Bookings(int driverPIN) {
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Integer[0];  // Return the list as an array
    }


    //5.11 Task 11 Find the average age of passengers with "Confirmed" bookings (i.e., booking_status is ”Confirmed”) on trips departing from a given city and within a specified date range
    @Override
    public Double getAvgAgeOfPassengersDepartFromCityBetweenTwoDates(String city, String start_date, String end_date) {
        Double averageAge = null;
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        return averageAge;
    }


    //5.12 Task 12 Find Passengers in a Given Trip.
    @Override
    public QueryResult.PassengerPINNameAgeMembershipStatus[] getPassengerInGivenTrip(int TripID) {
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.PassengerPINNameAgeMembershipStatus[0];
    }


    //5.13 Task 13 Find Drivers’ Scores
    @Override
    public QueryResult.DriverScoreRatingNumberOfBookingsPIN[] getDriversScores() {
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.DriverScoreRatingNumberOfBookingsPIN[0];
    }

    
    //5.14 Task 14 Find average ratings of drivers who have trips destined to each city
    @Override
    public QueryResult.CityAndAverageDriverRating[] getDriversAverageRatingsToEachDestinatedCity() {
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.CityAndAverageDriverRating[0];
    }


    //5.15 Task 15 Find total number of bookings of passengers for each membership status
    @Override
    public QueryResult.MembershipStatusAndTotalBookings[] getTotalBookingsEachMembershipStatus() {
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.MembershipStatusAndTotalBookings[0];
    }

    
    //5.16 Task 16 For the drivers' ratings, if rating is smaller than 2.0 or equal to 2.0, update the rating by adding 0.5.
    @Override
    public int updateDriverRatings() {
        int rowsUpdated = 0;
        
    	/*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/
    	
        return rowsUpdated;
    }
    

    //6.1 (Optional) Task 18 Find trips departing from the given city
    @Override
    public Trip[] getTripsFromCity(String city) {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Trip[0];
    }
    
    
    //6.2 (Optional) Task 19 Find all trips that have never been booked
    @Override
    public Trip[] getTripsWithNoBooks() {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Trip[0];
    }
    
    
    //6.3 (Optional) Task 20 For each driver, find the trip(s) with the highest number of bookings
    @Override
    public QueryResult.DriverPINandTripIDandNumberOfBookings[] getTheMostBookedTripsPerDriver() {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.DriverPINandTripIDandNumberOfBookings[0];
    }
    
    
    //6.4 (Optional) Task 21 Find Full Cars
    @Override
    public QueryResult.FullCars[] getFullCars() {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.FullCars[0];
    }

}
