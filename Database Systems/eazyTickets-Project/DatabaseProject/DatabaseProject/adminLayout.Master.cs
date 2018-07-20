using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace DatabaseProject
{
    public partial class adminLayout : System.Web.UI.MasterPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void Logout(object sender, EventArgs e)
        {
            Session["user"] = null;
            Session["type"] = null;

            Response.Redirect("./Sign_In.aspx");
        }
    }
}