using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace DatabaseProject
{
    public partial class AddShowtime : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void AddShowtime_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            int mid = int.Parse(Movieid.Text);
            int cid = int.Parse(CinemaID.Text);
            String time = hours.Text + ':' + minutes.Text + ':' + seconds.Text;
            DateTime date = SDate.SelectedDate;
            int seats = int.Parse(ASeats.Text);
            int cost = int.Parse(SCost.Text);
            String screening = SType.Text;

            DateTime datetime;

            bool flag = true;
            if (int.MinValue == cid)
            {
                Movieid.CssClass = Movieid.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (int.MinValue == cid)
            {
                Movieid.CssClass = CinemaID.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(time))
            {
                flag = false;
                hours.CssClass = hours.CssClass + " redBorder";
                minutes.CssClass = minutes.CssClass + " redBorder";
                seconds.CssClass = seconds.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (SDate.SelectedDate.Date == DateTime.MinValue)
            {
                flag = false;
                SDate.CssClass = SDate.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Showtime date is not selected";
            }
            if (int.MinValue == seats)
            {
                flag = false;
                ASeats.CssClass = ASeats.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (int.MinValue == cost)
            {
                flag = false;
                SCost.CssClass = SCost.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (string.IsNullOrWhiteSpace(screening))
            {
                flag = false;
                SType.CssClass = SType.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (flag)
            {
                datetime = date.Add(TimeSpan.Parse(time));

                int result = 0;
                int found = 1;
                found = objmyDAl.AddShowtime_DAL(mid, cid, datetime, seats, cost, screening, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Showtime has been added!";
                        Response.AddHeader("REFRESH", "1;URL=/adminHome.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Showtime already exists.";
                    }
                    else if (result == 2)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Showtime can only have '2d' or '3d' screening type.";
                    }
                    else if (result == 3)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Cinema doesn't exist.";
                    }
                    else if (result == 4)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Movie doesn't exist.";
                    }
                }
            }
        }
    }
}