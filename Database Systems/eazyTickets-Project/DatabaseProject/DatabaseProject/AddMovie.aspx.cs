using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;


namespace DatabaseProject
{
    public partial class AddMovie : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void AddMovie_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String movieName = movie.Text;
            String directorName = director.Text;
            String writerName = writer.Text;
            String rTime = hours.Text + ':' + minutes.Text + ':' + seconds.Text;
            DateTime ReleaseDate = RDate.SelectedDate;
            String movieGenre = Genre.Text;
            String movieCast = Cast.Text;
            String imageLink = @"\images\" + ImageUpload.FileName;

            bool flag = true;
            if (string.IsNullOrWhiteSpace(movieName))
            {
                movie.CssClass = movie.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;
            }
            if (string.IsNullOrWhiteSpace(rTime))
            {
                flag = false;
                hours.CssClass = hours.CssClass + " redBorder";
                minutes.CssClass = minutes.CssClass + " redBorder";
                seconds.CssClass = seconds.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (RDate.SelectedDate.Date == DateTime.MinValue)
            {
                flag = false;
                RDate.CssClass = RDate.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Release date is not selected";
            }
            if (string.IsNullOrWhiteSpace(movieGenre))
            {
                flag = false;
                Genre.CssClass = Genre.CssClass + " redBorder";
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

                int result = 0;
                int found = 1;
                found = objmyDAl.AddMovie_DAL(movieName, directorName, writerName, rTime, ReleaseDate, movieGenre, movieCast, imageLink, ref result);
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
                        Message.Text = "Movie has been added!";
                        Response.AddHeader("REFRESH", "1;URL=/adminHome.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Movie already exists.";
                    }
                }
            }
        }
    }
}