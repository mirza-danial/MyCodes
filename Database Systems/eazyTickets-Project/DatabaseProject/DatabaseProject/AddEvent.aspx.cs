using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

namespace DatabaseProject
{
    public partial class AddEvent : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void AddEvent_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String eventName = name.Text;
            String eventType = type.Text;
            String eventOrganizers = organizers.Text;
            String eventVenue = venue.Text;
            String eTime = hours.Text + ':' + minutes.Text + ':' + seconds.Text;
            DateTime Date = EDate.SelectedDate;
            int tickets;
            int cost;
            String imageLink = @"\images\" + ImageUpload.FileName;
            bool excep = true;
            DateTime datetime;

            bool flag = true;
            if (string.IsNullOrWhiteSpace(eventName))
            {
                name.CssClass = name.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(eventType))
            {
                type.CssClass = type.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(eventOrganizers))
            {
                organizers.CssClass = organizers.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(eventVenue))
            {
                venue.CssClass = venue.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(eTime))
            {
                flag = false;
                hours.CssClass = hours.CssClass + " redBorder";
                minutes.CssClass = minutes.CssClass + " redBorder";
                seconds.CssClass = seconds.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (EDate.SelectedDate.Date == DateTime.MinValue)
            {
                flag = false;
                EDate.CssClass = EDate.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Release date is not selected";
            }
            if (string.IsNullOrWhiteSpace(ATickets.Text))
            {
                flag = false;
                ATickets.CssClass = ATickets.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (string.IsNullOrWhiteSpace(ECost.Text))
            {
                flag = false;
                ECost.CssClass = ECost.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }

            if (!(ImageUpload.HasFile))
            {
                flag = false;
                ImageUpload.CssClass = ImageUpload.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Image isn't uploaded!";
            }

            if (flag)
            {

                tickets = int.Parse(ATickets.Text);
                cost = int.Parse(ECost.Text);

                StringBuilder sb = new StringBuilder();

                if (ImageUpload.HasFile)
                {
                    try
                    {
                        sb.AppendFormat(" Uploading file: {0}", ImageUpload.FileName);
                        //Showing the file information
                        sb.AppendFormat("<br/> Save As: {0}", ImageUpload.PostedFile.FileName);
                        sb.AppendFormat("<br/> File type: {0}", ImageUpload.PostedFile.ContentType);
                        sb.AppendFormat("<br/> File length: {0}", ImageUpload.PostedFile.ContentLength);
                        sb.AppendFormat("<br/> File name: {0}", ImageUpload.PostedFile.FileName);
                    }
                    catch (Exception ex)
                    {
                        sb.Append("<br/> Error <br/>");
                        sb.AppendFormat("Unable to save file <br/> {0}", ex.Message);
                        excep = false;
                    }
                }

                datetime = Date.Add(TimeSpan.Parse(eTime));

                int result = 0;
                int found = 1;
                found = objmyDAl.AddEvent_DAL(eventName, eventType, eventOrganizers, eventVenue, datetime, tickets, cost, imageLink, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        //saving the file
                        if(excep)
                            ImageUpload.SaveAs(Server.MapPath(@"~\images\" + ImageUpload.FileName));
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Event has been added!";
                        Response.AddHeader("REFRESH", "1;URL=/adminHome.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Event already exists.";
                    }
                    else if (result == 2)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Selected date has passed.";
                    }
                }
            }
        }
    }
}