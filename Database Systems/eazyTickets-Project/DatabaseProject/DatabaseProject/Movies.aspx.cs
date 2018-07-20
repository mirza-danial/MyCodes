using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using DatabaseProject;
using System.Data;
using System.Web.UI.HtmlControls;
using System.Data.SqlClient;
using System.Configuration;

namespace DatabaseProject
{
    public partial class Movies : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["user"] != null)
            {
                HtmlLink link = Page.Master.FindControl("layoutStyleSheet") as HtmlLink;
                link.Href = "css/secondary.css";
            }

            myDAL objmyDAl = new myDAL();
            DataTable DT = new DataTable();
            int found;
            found = objmyDAl.SelectCinemas_DAL(ref DT);
            if (found == 1)
            {
                Cinemas.DataSource = DT;
                Cinemas.DataBind();
            }

        }

        protected void OnItemDataBound(object sender, RepeaterItemEventArgs e)
        {
            if (e.Item.ItemType == ListItemType.Item || e.Item.ItemType == ListItemType.AlternatingItem)
            {
                string CinemaId = (e.Item.FindControl("CinemaId") as HiddenField).Value;
                Repeater Display = e.Item.FindControl("Display") as Repeater;
                myDAL objmyDAl = new myDAL();
                DataTable DT = new DataTable();
                int found;
                found = objmyDAl.SelectMovies_DAL(CinemaId,ref DT);
                if (found == 1)
                {
                    Display.DataSource = DT;
                    Display.DataBind();
                }
               
            }
        }

        protected void AddToCart_Click(object sender, EventArgs e)
        {
            if (Session["user"] != null)
            {
                LinkButton b = sender as LinkButton;
                string Quantity = Page.Request.Form[b.ToolTip.ToString()].ToString();
                bool flag = true;
                if (string.IsNullOrWhiteSpace(Quantity))
                {
                    Message.CssClass = "alert alert-danger";
                    Message.Text = "Please enter some quantity!";
                }
                if (flag)
                {
                    int ret;
                    myDAL objmyDAl = new myDAL();
                    int done = 0;
                    ret = objmyDAl.AddItemToCart_DAL(Session["user"].ToString(), b.ToolTip.ToString(), Quantity, ref done);
                    if (ret == 1)
                    {
                        if (done == 1)
                        {

                            Response.Redirect("./Movies.aspx");
                        }
                        else
                        {
                            Message.Text = "Not enough tickets";
                            //Show message for no enough tickets
                        }
                    }
                    else
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Please enter an appropriate numeric figure in quantity";
                        //execption;
                    }
                }

            }
            else
            {
                Response.Redirect("./Sign_In.aspx");
            }
        }
    
    }
}