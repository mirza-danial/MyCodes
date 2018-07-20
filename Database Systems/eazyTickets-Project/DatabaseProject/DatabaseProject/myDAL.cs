using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data;
using System.Data.SqlClient;


namespace DatabaseProject
{
    public class myDAL
    {
        private static readonly string connString =
            System.Configuration.ConfigurationManager.ConnectionStrings["sqlCon1"].ConnectionString;
        //Input: Name: StudentName which is to be searched
        //Input DataTable passed by refence and result will be return in this table.
        //Return int: 1 if successful 0 if error.

        public int Login_DAL(string Email, string Password, ref int retv)

        {

            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("logincheck", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@email", SqlDbType.VarChar, 30); //input of SQL stored procedure
                cmd.Parameters.Add("@password", SqlDbType.VarChar, 32);

                // set SQL procedure parameter values
                cmd.Parameters["@email"].Value = Email;
                cmd.Parameters["@password"].Value = Password;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;


                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int SignUp_DAL(string Fname, string Lname, string City, string Gender, string Phone, string Email, string Password, ref int retv)

        {

            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("signup", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@email", SqlDbType.VarChar, 30); //input of SQL stored procedure
                cmd.Parameters.Add("@password", SqlDbType.VarChar, 32);
                cmd.Parameters.Add("@fname", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@lname", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@city", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@gender", SqlDbType.Char, 1);
                cmd.Parameters.Add("@phone", SqlDbType.BigInt);


                // set SQL procedure parameter values
                cmd.Parameters["@email"].Value = Email;
                cmd.Parameters["@password"].Value = Password;
                cmd.Parameters["@fname"].Value = Fname;
                cmd.Parameters["@lname"].Value = Lname;
                cmd.Parameters["@city"].Value = City;
                cmd.Parameters["@phone"].Value = Phone;
                cmd.Parameters["@gender"].Value = Gender;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;


                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int ViewUser_DAL(String Email, ref String Fname, ref String Lname, ref String Phone, ref String City)

        {

            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("viewInfo", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@email", SqlDbType.VarChar, 30); //input of SQL stored procedure
               
                    

                // set SQL procedure parameter values
                cmd.Parameters["@email"].Value = Email;
                

                cmd.Parameters.Add(new SqlParameter("@fname", SqlDbType.VarChar,20));
                cmd.Parameters["@fname"].Direction = ParameterDirection.Output;

                cmd.Parameters.Add(new SqlParameter("@lname", SqlDbType.VarChar, 20));
                cmd.Parameters["@lname"].Direction = ParameterDirection.Output;

                cmd.Parameters.Add(new SqlParameter("@phone", SqlDbType.BigInt));
                cmd.Parameters["@phone"].Direction = ParameterDirection.Output;

                cmd.Parameters.Add(new SqlParameter("@city", SqlDbType.VarChar, 20));
                cmd.Parameters["@city"].Direction = ParameterDirection.Output;


                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                Fname = cmd.Parameters["@fname"].Value.ToString();
                Lname = cmd.Parameters["@lname"].Value.ToString();
                Phone = "+"+cmd.Parameters["@phone"].Value.ToString();
                City = cmd.Parameters["@city"].Value.ToString();
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int changePassword_DAL(string Email, string OldPassword, string NewPassword, ref int retv)

        {

            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("changePassword", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@email", SqlDbType.VarChar, 30); //input of SQL stored procedure
                cmd.Parameters.Add("@opass", SqlDbType.VarChar, 32);
                cmd.Parameters.Add("@npass", SqlDbType.VarChar, 32);

                // set SQL procedure parameter values
                cmd.Parameters["@email"].Value = Email;
                cmd.Parameters["@opass"].Value = OldPassword;
                cmd.Parameters["@npass"].Value = NewPassword;


                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;


                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }

        public int getEventCount_DAL(String Email,ref int retv)
        {

            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("eventCount", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@email", SqlDbType.VarChar, 30); //input of SQL stored procedure
               

                // set SQL procedure parameter values
                cmd.Parameters["@email"].Value = Email;
                ;


                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;


                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
       


        public int findNearbyEvent_DAL(String Email,ref DataTable data)
        {

            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("nearbyEvents", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@email", SqlDbType.VarChar, 30); //input of SQL stored procedure
                cmd.Parameters["@email"].Value = Email;
                cmd.ExecuteNonQuery(); //executre the cmd query
                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(data); //get results
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int SelectEvents_DAL(ref DataTable result)

        {

            int Found = 0;
            DataSet ds = new DataSet();
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("selectEvents", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.ExecuteNonQuery(); //executre the cmd query
                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(ds); //get results
                result = ds.Tables[0]; //fill the results in ref input table 
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int SelectConcerts_DAL(ref DataTable result)
        {
            DataSet ds = new DataSet();
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("selectConcerts", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.ExecuteNonQuery(); //executre the cmd query
                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(ds); //get results
                result = ds.Tables[0]; //fill the results in ref input table 
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int AddItemToCart_DAL(String User,String ticketId,String Quantity,ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            int ex;
           try
           {
                cmd = new SqlCommand("addToCart", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add(new SqlParameter("@user", SqlDbType.VarChar, 30));
               
                cmd.Parameters.Add(new SqlParameter("@ticket_id", SqlDbType.Int));
               
                cmd.Parameters.Add(new SqlParameter("@amount", SqlDbType.Int));
               
                cmd.Parameters["@user"].Value = User;
                cmd.Parameters["@ticket_id"].Value = int.Parse(ticketId);
                cmd.Parameters["@amount"].Value = int.Parse(Quantity);

                cmd.Parameters.Add(new SqlParameter("@ex", SqlDbType.Int));
                cmd.Parameters["@ex"].Direction = ParameterDirection.Output;
                cmd.Parameters.Add(new SqlParameter("@done", SqlDbType.Int));
                cmd.Parameters["@done"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query
                retv = int.Parse(cmd.Parameters["@done"].Value.ToString());
                ex = int.Parse(cmd.Parameters["@ex"].Value.ToString());

                con.Close(); //close SQL connection
           }
           catch
           {
              return 0;
           }
           finally
           {

             con.Close(); //close SQL connection
           }
            return ex;
        }
        public int ShopingCart_DAL(String User,ref DataTable result)
        {
            DataSet ds = new DataSet();
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("displayCart", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@user", SqlDbType.VarChar, 30));
                cmd.Parameters["@user"].Value = User;

                cmd.ExecuteNonQuery(); //executre the cmd query

                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(ds); //get results

                result = ds.Tables[0]; //fill the results in ref input table 
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int dropItem_DAL(String User,String TicketId)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("dropItem", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@user", SqlDbType.VarChar, 30));
                cmd.Parameters["@user"].Value = User;
                cmd.Parameters.Add(new SqlParameter("@ticketId", SqlDbType.Int));
                cmd.Parameters["@ticketId"].Value = int.Parse(TicketId.ToString());

                cmd.ExecuteNonQuery(); //executre the cmd query
                con.Close();
            }
            catch(SqlException ex)
            {
                return 0;
            }
            finally
            {
                con.Close();
            }
            return 1;
        }
        public int dropCart_DAL(String User)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("dropCart", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@user", SqlDbType.VarChar, 30));
                cmd.Parameters["@user"].Value = User;
                
                cmd.ExecuteNonQuery(); //executre the cmd query
                con.Close();
            }
            catch (SqlException ex)
            {
                return 0;
            }
            finally
            {
                con.Close();
            }
            return 1;
        }
        public int Upcoming_DAL(ref DataTable result)
        {
            DataSet ds = new DataSet();
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("upcoming", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.ExecuteNonQuery(); //executre the cmd query
                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(ds); //get results
                result = ds.Tables[0]; //fill the results in ref input table 
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int SelectCinemas_DAL(ref DataTable result)
        {
            DataSet ds = new DataSet();
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("selectCinemas", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
               
                cmd.ExecuteNonQuery(); //executre the cmd query
                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(ds); //get results
                result = ds.Tables[0]; //fill the results in ref input table 
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int SelectMovies_DAL(String CID,ref DataTable result)
        {
            DataSet ds = new DataSet();
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("selectMovies", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@cinemaId", SqlDbType.VarChar, 30));
                cmd.Parameters["@cinemaId"].Value = CID;
                cmd.ExecuteNonQuery(); //executre the cmd query
                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(ds); //get results
                result = ds.Tables[0]; //fill the results in ref input table 
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int ConfirmOrder_DAL(String User)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("ConfirmOrder", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@user", SqlDbType.VarChar, 30));
                cmd.Parameters["@user"].Value = User;

                cmd.ExecuteNonQuery(); //executre the cmd query
                con.Close();
            }
            catch (SqlException ex)
            {
                return 0;
            }
            finally
            {
                con.Close();
            }
            return 1;
        }
        public int MessageSend_DAL(string email, string message, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("ContactMessage", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@email", SqlDbType.VarChar, 30); //input of SQL stored procedure
                cmd.Parameters.Add("@message", SqlDbType.VarChar, 200);


                // set SQL procedure parameter values
                cmd.Parameters["@email"].Value = email;
                cmd.Parameters["@message"].Value = message;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;


                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;

        }
        public int ReveiwRating_DAL(String User,int Rating,String Reveiw,int Id,ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
          // try
           //{
                cmd = new SqlCommand("AddRating", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@user", SqlDbType.VarChar, 30));
                cmd.Parameters["@user"].Value = User;
                cmd.Parameters.Add(new SqlParameter("@ticket_id", SqlDbType.Int));
                cmd.Parameters["@ticket_id"].Value = Id ;
                cmd.Parameters.Add(new SqlParameter("@rating", SqlDbType.Int));
                cmd.Parameters["@rating"].Value = Rating;
                cmd.Parameters.Add(new SqlParameter("@review", SqlDbType.VarChar, 100));
                cmd.Parameters["@review"].Value = Reveiw;
                cmd.Parameters.Add(new SqlParameter("@out", SqlDbType.Int));
                cmd.Parameters["@out"].Direction = ParameterDirection.Output;
                cmd.ExecuteNonQuery(); //executre the cmd query
                retv = int.Parse(cmd.Parameters["@out"].Value.ToString());
                con.Close();
           /*}
           catch (SqlException ex)
           {
                return 0;
           }
           finally
           {
              con.Close();
           }*/
           return 1;
        }
        public int ViewOrders_DAL(String  User, ref DataTable result)
        {
            DataSet ds = new DataSet();
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("getOrderDetails", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@user", SqlDbType.VarChar, 30));
                cmd.Parameters["@user"].Value =User;
                cmd.ExecuteNonQuery(); //executre the cmd query
                using (SqlDataAdapter da = new SqlDataAdapter(cmd))
                    da.Fill(ds); //get results
                result = ds.Tables[0]; //fill the results in ref input table 
                con.Close(); //close SQL connection
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        
        public int AddMovie_DAL(string movieName, string directorName, string writerName, string rTime, DateTime ReleaseDate, string movieGenre, string movieCast, string imageLink, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("AddMovie", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@movieName", SqlDbType.VarChar, 30); //input of SQL stored procedure
                cmd.Parameters.Add("@director", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@writer", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@runningTime", SqlDbType.Time);
                cmd.Parameters.Add("@rDate", SqlDbType.Date);
                cmd.Parameters.Add("@genre", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@mainCast", SqlDbType.VarChar, 100);
                cmd.Parameters.Add("@ImageLink", SqlDbType.VarChar, 100);

                // set SQL procedure parameter values
                cmd.Parameters["@movieName"].Value = movieName;
                cmd.Parameters["@director"].Value = directorName;
                cmd.Parameters["@writer"].Value = writerName;
                cmd.Parameters["@runningTime"].Value = rTime;
                cmd.Parameters["@rDate"].Value = ReleaseDate;
                cmd.Parameters["@genre"].Value = movieGenre;
                cmd.Parameters["@mainCast"].Value = movieCast;
                cmd.Parameters["@ImageLink"].Value = imageLink;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0
            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int AddAdmin_DAL(int id, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("AddAdmin", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@id", SqlDbType.Int); //input of SQL stored procedure

                // set SQL procedure parameter values
                cmd.Parameters["@id"].Value = id;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int DelMovie_DAL(int id, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("DelMovie", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@id", SqlDbType.Int); //input of SQL stored procedure

                // set SQL procedure parameter values
                cmd.Parameters["@id"].Value = id;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int AddShowtime_DAL(int movieid, int cinemaid, DateTime datetime, int seats, int cost, string type, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("addShowtime", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@movieId", SqlDbType.Int); //input of SQL stored procedure
                cmd.Parameters.Add("@CinemaId", SqlDbType.Int);
                cmd.Parameters.Add("@date_time", SqlDbType.DateTime);
                cmd.Parameters.Add("@seats", SqlDbType.Int);
                cmd.Parameters.Add("@cost", SqlDbType.Int);
                cmd.Parameters.Add("@screentype", SqlDbType.Char, 2);

                // set SQL procedure parameter values
                cmd.Parameters["@movieId"].Value = movieid;
                cmd.Parameters["@CinemaId"].Value = cinemaid;
                cmd.Parameters["@date_time"].Value = datetime;
                cmd.Parameters["@seats"].Value = seats;
                cmd.Parameters["@cost"].Value = cost;
                cmd.Parameters["@screentype"].Value = type;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0
            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int DelShowtime_DAL(int id, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("removeShowtime", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@Showid", SqlDbType.Int); //input of SQL stored procedure

                // set SQL procedure parameter values
                cmd.Parameters["@Showid"].Value = id;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int AddCinema_DAL(string name, string location, int phone, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("addCinema", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@Name", SqlDbType.VarChar, 50); //input of SQL stored procedure
                cmd.Parameters.Add("@location", SqlDbType.VarChar, 100);
                cmd.Parameters.Add("@ContactNo", SqlDbType.Int);

                // set SQL procedure parameter values
                cmd.Parameters["@Name"].Value = name;
                cmd.Parameters["@location"].Value = location;
                cmd.Parameters["@ContactNo"].Value = phone;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0
            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int AddEvent_DAL(string eventName, string eventType, string eventOrganizer, string eventVenue, DateTime datetime, int tickets, int cost, string imageLink, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("addEvent", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@Name", SqlDbType.VarChar, 30); //input of SQL stored procedure
                cmd.Parameters.Add("@type", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@organizer", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@venue", SqlDbType.VarChar, 100);
                cmd.Parameters.Add("@day_time", SqlDbType.DateTime);
                cmd.Parameters.Add("@tickets", SqlDbType.Int);
                cmd.Parameters.Add("@cost", SqlDbType.Int);
                cmd.Parameters.Add("@ImageLink", SqlDbType.VarChar, 100);


                // set SQL procedure parameter values
                cmd.Parameters["@Name"].Value = eventName;
                cmd.Parameters["@type"].Value = eventType;
                cmd.Parameters["@organizer"].Value = eventOrganizer;
                cmd.Parameters["@venue"].Value = eventVenue;
                cmd.Parameters["@day_time"].Value = datetime;
                cmd.Parameters["@tickets"].Value = tickets;
                cmd.Parameters["@cost"].Value = cost;
                cmd.Parameters["@ImageLink"].Value = imageLink;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0
            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int DelEvent_DAL(int id, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("removeEvent", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@Eventid", SqlDbType.Int); //input of SQL stored procedure

                // set SQL procedure parameter values
                cmd.Parameters["@Eventid"].Value = id;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int AddConcert_DAL(string concertVenue, DateTime datetime, string concertPerformer, string concertOrganizers, int tickets, int cost, string imageLink, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("addConcert", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@venue", SqlDbType.VarChar, 100); //input of SQL stored procedure
                cmd.Parameters.Add("@DayTime", SqlDbType.DateTime);
                cmd.Parameters.Add("@performer", SqlDbType.VarChar, 30);
                cmd.Parameters.Add("@organizer", SqlDbType.VarChar, 20);
                cmd.Parameters.Add("@seats", SqlDbType.Int);
                cmd.Parameters.Add("@cost", SqlDbType.Int);
                cmd.Parameters.Add("@ImageLink", SqlDbType.VarChar, 100);


                // set SQL procedure parameter values
                cmd.Parameters["@venue"].Value = concertVenue;
                cmd.Parameters["@DayTime"].Value = datetime;
                cmd.Parameters["@performer"].Value = concertPerformer;
                cmd.Parameters["@organizer"].Value = concertOrganizers;
                cmd.Parameters["@seats"].Value = tickets;
                cmd.Parameters["@cost"].Value = cost;
                cmd.Parameters["@ImageLink"].Value = imageLink;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0
            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
        public int DelConcert_DAL(int id, ref int retv)
        {
            SqlConnection con = new SqlConnection(connString);
            con.Open();
            SqlCommand cmd;
            try
            {
                cmd = new SqlCommand("removeConcert", con); //name of your SQL procedure
                cmd.CommandType = CommandType.StoredProcedure;

                cmd.Parameters.Add("@ConcertId", SqlDbType.Int); //input of SQL stored procedure

                // set SQL procedure parameter values
                cmd.Parameters["@ConcertId"].Value = id;

                cmd.Parameters.Add(new SqlParameter("@output", SqlDbType.Int));
                cmd.Parameters["@output"].Direction = ParameterDirection.Output;

                cmd.ExecuteNonQuery(); //executre the cmd query

                con.Close(); //close SQL connection

                retv = int.Parse(cmd.Parameters["@output"].Value.ToString());
            }
            catch (SqlException ex)
            {
                return 0; //if any erron return 0

            }
            finally
            {
                con.Close();
            }

            return 1; //if no error return 1;
        }
    }
}