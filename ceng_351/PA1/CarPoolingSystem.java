package ceng.ceng351.carpoolingdb;

import com.mysql.cj.x.protobuf.MysqlxDatatypes;

import javax.swing.plaf.nimbus.State;
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
        String query = "SELECT PIN, rating FROM Drivers ORDER BY PIN ASC;";

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

        String createParticipantsTable = "CREATE TABLE IF NOT EXISTS Participants (" +
                "PIN INT PRIMARY KEY," +
                "p_name VARCHAR(50)," +
                "age INT" +
                ");";

        String createPassengersTable = "CREATE TABLE IF NOT EXISTS Passengers (" +
                "PIN INT PRIMARY KEY," +
                "membership_status VARCHAR(50)," +
                "FOREIGN KEY (PIN) REFERENCES Participants(PIN)" +
                ");";

        String createDriversTable =  "CREATE TABLE IF NOT EXISTS Drivers (" +
                "PIN INT PRIMARY KEY," +
                "rating DOUBLE," +
                "FOREIGN KEY (PIN) REFERENCES Participants(PIN)" +
                ");";

        String createCarsTable = "CREATE TABLE IF NOT EXISTS Cars (" +
                "CarID INT PRIMARY KEY," +
                "PIN INT," +
                "color VARCHAR(50)," +
                "brand VARCHAR(50)," +
                "FOREIGN KEY (PIN) REFERENCES Drivers(PIN)" +
                ");";

        String createTripsTable = "CREATE TABLE IF NOT EXISTS Trips (" +
                "TripID INT PRIMARY KEY," +
                "CarID INT," +
                "date VARCHAR(50)," +
                "departure VARCHAR(50)," +
                "destination VARCHAR(50)," +
                "num_seats_available INT," +
                "FOREIGN KEY (CarID) REFERENCES Cars(CarID)" +
                ");";

        String createBookingsTable =  "CREATE TABLE IF NOT EXISTS Bookings (" +
                "TripID INT," +
                "PIN INT," +
                "booking_status VARCHAR(50)," +
                "PRIMARY KEY (TripID, PIN)," +
                "FOREIGN KEY (TripID) REFERENCES Trips(TripID)," +
                "FOREIGN KEY (PIN) REFERENCES Passengers(PIN)" +
                ");";

        try (Statement statement = this.connection.createStatement()) {
            try {
                statement.executeUpdate(createParticipantsTable);
                tableCount++;
            } catch (SQLException e) {
                System.err.println("Failed to create Participants table: " + e.getMessage());
            }
            try {
                statement.executeUpdate(createPassengersTable);
                tableCount++;
            } catch (SQLException e) {
                System.err.println("Failed to create Passengers table: " + e.getMessage());
            }
            try {
                statement.executeUpdate(createDriversTable);
                tableCount++;
            } catch (SQLException e) {
                System.err.println("Failed to create Drivers table: " + e.getMessage());
            }
            try {
                statement.executeUpdate(createCarsTable);
                tableCount++;
            } catch (SQLException e) {
                System.err.println("Failed to create Cars table: " + e.getMessage());
            }
            try {
                statement.executeUpdate(createTripsTable);
                tableCount++;
            } catch (SQLException e) {
                System.err.println("Failed to create Trips table: " + e.getMessage());
            }
            try {
                statement.executeUpdate(createBookingsTable);
                tableCount++;
            } catch (SQLException e) {
                System.err.println("Failed to create Bookings table: " + e.getMessage());
            }
        } catch (SQLException e) {
            System.err.println("Failed to create statement: " + e.getMessage());
        }
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

        String[] tableNames = {"Bookings", "Trips", "Cars", "Passengers", "Drivers", "Participants"};


        for (String table : tableNames) {
            String abc = "DROP TABLE " + table;
            try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
                preparedStatement.executeUpdate();
                tableCount++;
            } catch (SQLException e) {
            }
        }


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

        String abc = "INSERT INTO Participants(" +
                "PIN," +
                "p_name," +
                "age" +
                ")" +
                "VALUES(" +
                "?," +
                "?," +
                "?" +
                ");";
        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)){
            for (Participant participant : participants) {
                preparedStatement.setInt(1,participant.getPIN());
                preparedStatement.setString(2,participant.getP_name());
                preparedStatement.setInt(3,participant.getAge());

                try{
                    rowsInserted += preparedStatement.executeUpdate();
                } catch (SQLException e) {
                    System.err.println("Failed to insert participant with PIN "
                            + participant.getPIN() + ": " + e.getMessage());
                }
            }
        } catch (SQLException e) {
            // Handle connection or statement issues
            System.err.println("Failed to execute insertParticipants: " + e.getMessage());
        }
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

        String abc = "INSERT INTO Passengers(" +
                "PIN," +
                "membership_status" +
                ")" +
                "VALUES(" +
                "?," +
                "?" +
                ");";
        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)){
            for (Passenger passenger : passengers) {
                preparedStatement.setInt(1,passenger.getPIN());
                preparedStatement.setString(2,passenger.getMembership_status());

                try{
                    rowsInserted += preparedStatement.executeUpdate();
                } catch (SQLException e) {
                    System.err.println("Failed to insert passenger with PIN "
                            + passenger.getPIN() + ": " + e.getMessage());
                }
            }
        } catch (SQLException e) {
            // Handle connection or statement issues
            System.err.println("Failed to execute insertPassengers: " + e.getMessage());
        }

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

        String abc = "INSERT INTO Drivers(" +
                "PIN," +
                "rating" +
                ")" +
                "VALUES(" +
                "?," +
                "?" +
                ");";
        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)){
            for (Driver driver : drivers) {
                preparedStatement.setInt(1,driver.getPIN());
                preparedStatement.setDouble(2,driver.getRating());

                try{
                    rowsInserted += preparedStatement.executeUpdate();
                } catch (SQLException e) {
                    System.err.println("Failed to insert driver with PIN "
                            + driver.getPIN() + ": " + e.getMessage());
                }
            }
        } catch (SQLException e) {
            // Handle connection or statement issues
            System.err.println("Failed to execute insertDrivers: " + e.getMessage());
        }

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

        String abc = "INSERT INTO Cars(" +
                "CarID," +
                "PIN," +
                "color," +
                "brand" +
                ")" +
                "VALUES(" +
                "?," +
                "?," +
                "?," +
                "?" +
                ");";
        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)){
            for (Car car : cars) {
                preparedStatement.setInt(1,car.getCarID());
                preparedStatement.setInt(2,car.getPIN());
                preparedStatement.setString(3,car.getColor());
                preparedStatement.setString(4,car.getBrand());

                try{
                    rowsInserted += preparedStatement.executeUpdate();
                } catch (SQLException e) {
                    System.err.println("Failed to insert car with CarID "
                            + car.getCarID() + ": " + e.getMessage());
                }
            }
        } catch (SQLException e) {
            // Handle connection or statement issues
            System.err.println("Failed to execute insertCars: " + e.getMessage());
        }

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

        String abc = "INSERT INTO Trips(" +
                "TripID," +
                "CarID," +
                "date," +
                "departure," +
                "destination," +
                "num_seats_available" +
                ")" +
                "VALUES(" +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?" +
                ");";
        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)){
            for (Trip trip : trips) {
                preparedStatement.setInt(1,trip.getTripID());
                preparedStatement.setInt(2,trip.getCarID());
                preparedStatement.setString(3,trip.getDate());
                preparedStatement.setString(4,trip.getDeparture());
                preparedStatement.setString(5,trip.getDestination());
                preparedStatement.setInt(6,trip.getNum_seats_available());

                try{
                    rowsInserted += preparedStatement.executeUpdate();
                } catch (SQLException e) {
                    System.err.println("Failed to insert trip with TripID "
                            + trip.getTripID() + ": " + e.getMessage());
                }
            }
        } catch (SQLException e) {
            // Handle connection or statement issues
            System.err.println("Failed to execute insertTrips: " + e.getMessage());
        }

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

        String abc = "INSERT INTO Bookings(" +
                "TripID," +
                "PIN," +
                "booking_status" +
                ")" +
                "VALUES(" +
                "?," +
                "?," +
                "?" +
                ");";
        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)){
            for (Booking booking : bookings) {
                preparedStatement.setInt(1,booking.getTripID());
                preparedStatement.setInt(2,booking.getPIN());
                preparedStatement.setString(3,booking.getBooking_status());

                try{
                    rowsInserted += preparedStatement.executeUpdate();
                } catch (SQLException e) {
                    System.err.println("Failed to insert booking with TripID and PIN "
                            + booking.getTripID() + ": " + e.getMessage());
                }
            }
        } catch (SQLException e) {
            // Handle connection or statement issues
            System.err.println("Failed to execute insertBookings: " + e.getMessage());
        }

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

        String BothPassAndDrivers = "SELECT p.PIN, p.p_name, p.age " +
                "FROM Participants p " +
                "WHERE p.PIN IN (" +
                "SELECT pass.PIN " +
                "FROM Passengers pass " +
                "INTERSECT " +
                "SELECT drivers.PIN " +
                "FROM Drivers drivers " +
                ") " +
                "ORDER BY p.PIN ASC";

        List<Participant> participants = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(BothPassAndDrivers)) {
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int pin = resultSet.getInt("PIN");
                String name = resultSet.getString("p_name");
                int age = resultSet.getInt("age");

                participants.add(new Participant(pin, name, age));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing getBothPassengersAndDrivers: " + e.getMessage());
        }

        return participants.toArray(new Participant[0]);
    }


    //5.4 Task 4 Find the PINs, names, ages, and ratings of drivers who do not own any cars
    @Override
    public QueryResult.DriverPINNameAgeRating[] getDriversWithNoCars() {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String DriversWithNoCars =  "SELECT p.PIN, p.p_name, p.age, d.rating " +
                "FROM Participants p , Drivers d " +
                "WHERE p.PIN = d.PIN AND p.PIN IN (" +
                "SELECT d2.PIN " +
                "FROM Drivers d2 " +
                "EXCEPT " +
                "SELECT c.PIN " +
                "FROM Cars c " +
                ") " +
                "ORDER BY p.PIN ASC";

        List<QueryResult.DriverPINNameAgeRating> drivers = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(DriversWithNoCars)) {
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int pin = resultSet.getInt("PIN");
                String name = resultSet.getString("p_name");
                int age = resultSet.getInt("age");
                double rating = resultSet.getDouble("rating");

                drivers.add(new QueryResult.DriverPINNameAgeRating(pin, name, age, rating));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing getBothPassengersAndDrivers: " + e.getMessage());
        }

        return drivers.toArray(new QueryResult.DriverPINNameAgeRating[0]);
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

        String abc = "DELETE " +
                "FROM Drivers " +
                "WHERE PIN NOT IN (" +
                "SELECT c.PIN " +
                "FROM Cars c " +
                ")";
        try (PreparedStatement pstmt = connection.prepareStatement(abc)) {
            rowsDeleted = pstmt.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Failed to delete drivers with no cars: " + e.getMessage());
        }
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

        String abc = "SELECT c.CarID, c.PIN, c.color, c.brand " +
                "FROM Cars c " +
                "WHERE c.CarID NOT IN (" +
                "SELECT t.CarID " +
                "FROM Trips t " +
                ") " +
                "ORDER BY c.CarID ASC";

        List<Car> cars = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int CarID = resultSet.getInt("CarID");
                int PIN = resultSet.getInt("PIN");
                String color = resultSet.getString("color");
                String brand = resultSet.getString("brand");

                cars.add(new Car(CarID, PIN, color, brand));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getCarsWithNoTrips" + e.getMessage());
        }

        return cars.toArray(new Car[0]);

    }


    //5.7 Task 7 Find all passengers who didn't book any trips
    @Override
    public Passenger[] getPassengersWithNoBooks() {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String abc = "SELECT p.PIN, p.membership_status " +
                "FROM Passengers p " +
                "WHERE p.PIN NOT IN (" +
                "SELECT b.PIN " +
                "FROM Bookings b " +
                ") " +
                "ORDER BY p.PIN ASC";

        List<Passenger> passengers = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int PIN = resultSet.getInt("PIN");
                String membership_status = resultSet.getString("membership_status");

                passengers.add(new Passenger(PIN, membership_status));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getPassengersWithNoBooks" + e.getMessage());
        }

        return passengers.toArray(new Passenger[0]);

    }


    //5.8 Task 8 Find all trips that depart from the specified city to specified destination city on specific date
    @Override
    public Trip[] getTripsFromToCitiesOnSpecificDate(String departure, String destination, String date) {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String abc = "SELECT * " +
                "FROM Trips t " +
                "WHERE t.departure = ? AND t.destination = ? AND t.date = ? " +
                "ORDER BY t.date ASC";

        List<Trip> trips = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            preparedStatement.setString(1, departure);
            preparedStatement.setString(2, destination);
            preparedStatement.setString(3, date);

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int TripID = resultSet.getInt("TripID");
                int CarID = resultSet.getInt("CarID");
                String date2 = resultSet.getString("date");
                String departure2 = resultSet.getString("departure");
                String destination2 = resultSet.getString("destination");
                int num_seats_available = resultSet.getInt("num_seats_available");

                trips.add(new Trip(TripID, CarID, date2, departure2, destination2, num_seats_available));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getTripsFromToCitiesOnSpecificDate" + e.getMessage());
        }

        return trips.toArray(new Trip[0]);
    }


    //5.9 Task 9 Find the PINs, names, ages, and membership_status of passengers who have bookings on all trips destined at a particular city
    @Override
    public QueryResult.PassengerPINNameAgeMembershipStatus[] getPassengersWithBookingsToAllTripsForCity(String city) {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String abc = "SELECT p.PIN, p.p_name, p.age,  pass.membership_status " +
                "FROM Passengers pass , Participants p " +
                "WHERE pass.PIN = p.PIN AND NOT EXISTS (" +
                "SELECT t.TripID " +
                "FROM Trips t " +
                "WHERE t.destination = ? AND NOT EXISTS ( " +
                "SELECT b.TripID " +
                "FROM Bookings b " +
                "WHERE b.PIN = pass.PIN AND b.TripID = t.TripID " +
                ") " +
                ") " +
                "ORDER BY p.PIN ASC";

        List<QueryResult.PassengerPINNameAgeMembershipStatus> passengers = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            preparedStatement.setString(1, city);

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int PIN = resultSet.getInt("PIN");
                String p_name = resultSet.getString("p_name");
                int p_age = resultSet.getInt("age");
                String membership_status = resultSet.getString("membership_status");


                passengers.add(new QueryResult.PassengerPINNameAgeMembershipStatus(PIN,p_name,p_age,membership_status));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : PassengerPINNameAgeMembershipStatus" + e.getMessage());
        }

        return passengers.toArray(new QueryResult.PassengerPINNameAgeMembershipStatus[0]);
    }


    //5.10 Task 10 For a given driver PIN, find the CarIDs that the driver owns and were booked at most twice.    
    @Override
    public Integer[] getDriverCarsWithAtMost2Bookings(int driverPIN) {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String abc = "SELECT c.CarID " +
                "FROM Cars c " +
                "WHERE c.PIN = ? AND ((" +
                "SELECT COUNT(*) " +
                "FROM Trips t, Bookings b " +
                "WHERE t.TripID = b.TripID AND t.CarID = c.CarID " +
                ") <= 2 ) " +
                "ORDER BY c.CarID ASC";

        List<Integer> cars = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            preparedStatement.setInt(1, driverPIN);
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int CarID = resultSet.getInt("CarID");
                cars.add(new Integer(CarID));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getDriverCarsWithAtMost2Bookings" + e.getMessage());
        }

        return cars.toArray(new Integer[0]);

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

        String abc = "SELECT AVG(p.age) " +
                "FROM Trips t , Bookings b, Participants p " +
                "WHERE b.booking_status = 'Confirmed' AND " +
                "t.TripID = b.TripID AND " +
                "b.PIN = p.PIN AND " +
                "t.departure = ? AND " +
                "? <= t.date AND " +
                "t.date <= ? " ;


        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            preparedStatement.setString(1, city);
            preparedStatement.setString(2, start_date);
            preparedStatement.setString(3, end_date);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                averageAge = resultSet.getDouble(1);
                if (resultSet.wasNull()) {
                    averageAge = null;
                }
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getAvgAgeOfPassengersDepartFromCityBetweenTwoDates" + e.getMessage());
        }

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

        String abc = "SELECT p.PIN , p.p_name , p.age , pass.membership_status " +
                "FROM Trips t, Bookings b, Participants p, Passengers pass " +
                "WHERE pass.PIN = p.PIN AND p.PIN = b.PIN AND t.TripID = b.TripID AND t.TripID = ? " +
                "ORDER BY b.PIN ASC";

        List<QueryResult.PassengerPINNameAgeMembershipStatus> passengers = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            preparedStatement.setInt(1, TripID);

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                int PIN = resultSet.getInt("PIN");
                String p_name = resultSet.getString("p_name");
                int p_age = resultSet.getInt("age");
                String membership_status = resultSet.getString("membership_status");


                passengers.add(new QueryResult.PassengerPINNameAgeMembershipStatus(PIN,p_name,p_age,membership_status));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getPassengerInGivenTrip" + e.getMessage());
        }

        return passengers.toArray(new QueryResult.PassengerPINNameAgeMembershipStatus[0]);
    }


    //5.13 Task 13 Find Drivers’ Scores
    @Override
    public QueryResult.DriverScoreRatingNumberOfBookingsPIN[] getDriversScores() {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String abc = "SELECT d.PIN AS driverPIN, " +
                "d.rating AS rating2, " +
                "COUNT(b.TripID) AS numberOfBookings, " +
                "COUNT(b.TripID) * d.rating AS driver_score " +
                "FROM Drivers d , Trips t , Bookings b , Cars c " +
                "WHERE d.PIN = c.PIN AND c.CarID = t.CarID AND t.TripID = b.TripID " +
                "GROUP BY d.PIN " +
                "ORDER BY driver_score DESC, d.PIN ASC";

        List<QueryResult.DriverScoreRatingNumberOfBookingsPIN> driverScores = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                double driver_score = resultSet.getDouble("driver_score");
                double rating = resultSet.getDouble("rating2");
                int numberOfBookings = resultSet.getInt("numberOfBookings");
                int DriverPIN = resultSet.getInt("driverPIN");


                driverScores.add(new QueryResult.DriverScoreRatingNumberOfBookingsPIN(driver_score,rating,numberOfBookings,DriverPIN));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getDriversScores" + e.getMessage());
        }

        return driverScores.toArray(new QueryResult.DriverScoreRatingNumberOfBookingsPIN[0]);
    }


    //5.14 Task 14 Find average ratings of drivers who have trips destined to each city
    @Override
    public QueryResult.CityAndAverageDriverRating[] getDriversAverageRatingsToEachDestinatedCity() {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String abc = "SELECT AVG(d.rating) AS average_rating_of_drivers , t.destination AS destination_city " +
                "FROM Drivers d, Trips t, Cars c " +
                "WHERE c.CarID = t.CarID AND c.PIN = d.PIN " +
                "GROUP BY t.destination " +
                "ORDER BY t.destination ASC";

        List<QueryResult.CityAndAverageDriverRating> cityAndAverageDriverRatings = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {

            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                double average_rating_of_drivers = resultSet.getDouble("average_rating_of_drivers");
                String destination_city = resultSet.getString("destination_city");

                cityAndAverageDriverRatings.add(new QueryResult.CityAndAverageDriverRating(destination_city,average_rating_of_drivers));
            }

            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getDriversAverageRatingsToEachDestinatedCity" + e.getMessage());
        }

        return cityAndAverageDriverRatings.toArray(new QueryResult.CityAndAverageDriverRating[0]);
    }


    //5.15 Task 15 Find total number of bookings of passengers for each membership status
    @Override
    public QueryResult.MembershipStatusAndTotalBookings[] getTotalBookingsEachMembershipStatus() {

        /*****************************************************/
        /*****************************************************/
        /*********************  TODO  ***********************/
        /*****************************************************/
        /*****************************************************/

        String abc = "SELECT COUNT(b.TripID) AS total_number_of_bookings, p.membership_status AS membership_status " +
                "FROM Bookings b, Passengers p " +
                "WHERE b.PIN = p.PIN " +
                "GROUP BY p.membership_status " +
                "ORDER BY p.membership_status ASC";

        List<QueryResult.MembershipStatusAndTotalBookings> membershipStatusAndTotalBookings = new ArrayList<>();

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            ResultSet resultSet = preparedStatement.executeQuery();

            while (resultSet.next()) {
                String membership_status = resultSet.getString("membership_status");
                int total_number_of_bookings = resultSet.getInt("total_number_of_bookings");

                membershipStatusAndTotalBookings.add(new QueryResult.MembershipStatusAndTotalBookings(membership_status,total_number_of_bookings));
            }
            resultSet.close();
        } catch (SQLException e) {
            System.err.println("Error executing : getTotalBookingsEachMembershipStatus" + e.getMessage());
        }

        return membershipStatusAndTotalBookings.toArray(new QueryResult.MembershipStatusAndTotalBookings[0]);
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

        String abc = "UPDATE Drivers " +
                "SET rating = rating + 0.5 " +
                "WHERE rating <= 2.0 ";

        try (PreparedStatement preparedStatement = connection.prepareStatement(abc)) {
            rowsUpdated = preparedStatement.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error executing updateDriverRatings: " + e.getMessage());
        }

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

