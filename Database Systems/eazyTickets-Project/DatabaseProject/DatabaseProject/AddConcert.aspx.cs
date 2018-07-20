using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

namespace DatabaseProject
{
    public partial class AddConcert : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void AddConcert_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String concertVenue = venue.Text;
            String cTime = hours.Text + ':' + minutes.Text + ':' + seconds.Text;
            DateTime Date = CDate.SelectedDate;

            String concertPerformer = performer.Text;
            String concertOrganizers = organizers.Text;
            int tickets;
            int cost;
            String imageLink = @"\images\" + ImageUpload.FileName;

            DateTime datetime;

            bool flag = true;
            if (string.IsNullOrWhiteSpace(concertVenue))
            {
                venue.CssClass = venue.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(cTime))
            {
                flag = false;
                hours.CssClass = hours.CssClass + " redBorder";
                minutes.CssClass = minutes.CssClass + " redBorder";
                seconds.CssClass = seconds.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (CDate.SelectedDate.Date == DateTime.MinValue)
            {
                flag = false;
                CDate.CssClass = CDate.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Release date is not selected";
            }
            if (string.IsNullOrWhiteSpace(concertPerformer))
            {
                performer.CssClass = performer.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(concertOrganizers))
            {
                organizers.CssClass = organizers.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(ATickets.Text))
            {
                flag = false;
                ATickets.CssClass = ATickets.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (string.IsNullOrWhiteSpace(CCost.Text))
            {
                flag = false;
                CCost.CssClass = CCost.CssClass + " redBorder";
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
                cost = int.Parse(CCost.Text);

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
                    }
                }

                datetime = Date.Add(TimeSpan.Parse(cTime));

                int result = 0;
                int found = 1;
                found = objmyDAl.AddConcert_DAL(concertVenue, datetime, concertPerformer, concertOrganizers, tickets, cost, imageLink, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        //saving the file
                        ImageUpload.SaveAs(Server.MapPath(@"~\images\" + ImageUpload.FileName));
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Concert has been added!";
                        Response.AddHeader("REFRESH", "1;URL=/adminHome.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Concert already exists.";
                    }
                }
            }
        }
    }
}