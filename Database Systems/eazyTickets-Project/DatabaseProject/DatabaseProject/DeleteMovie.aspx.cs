using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace DatabaseProject
{
    public partial class DeleteMovie : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void DelMovie_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            int id = int.Parse(MovieID.Text);

            bool flag = true;
            if (int.MinValue == id)
            {
                flag = false;
                MovieID.CssClass = MovieID.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (flag)
            {
                int result = 0;
                int found = 1;
                found = objmyDAl.DelMovie_DAL(id, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Movie has been deleted!";
                        Response.AddHeader("REFRESH", "1;URL=/adminHome.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Movie doesn't exist.";
                    }
                }
            }
        }
    }
}