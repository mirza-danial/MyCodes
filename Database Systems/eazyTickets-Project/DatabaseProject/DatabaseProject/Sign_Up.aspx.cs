using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using DatabaseProject;
using System.Data;

namespace DatabaseProject
{
    public partial class Sign_Up : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void SignUpButton_Click(object sender, EventArgs e)
        {
            myDAL objmyDAl = new myDAL();
            String InputEmail = Email.Text;
            String InputPassword = Password.Text;
            String InputFname = Fname.Text;
            String InputLname = Lname.Text;
            String InputPhone = Phone.Text;
            String InputGender = Gender.Text;
            String InputCity = City.Text;
            bool flag = true;
            if (string.IsNullOrWhiteSpace(InputEmail))
            {
                Email.CssClass = Email.CssClass + " redBorder";
                Message.Text = "Some Fields are empty!";
                Message.CssClass = "alert alert-danger";
                flag = false;

            }
            if (string.IsNullOrWhiteSpace(InputPassword))
            {
                flag = false;
                Password.CssClass = Password.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (string.IsNullOrWhiteSpace(InputPhone))
            {
                flag = false;
                Phone.CssClass = Phone.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (string.IsNullOrWhiteSpace(InputFname))
            {
                flag = false;
                Fname.CssClass = Fname.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (string.IsNullOrWhiteSpace(InputLname))
            {
                flag = false;
                Lname.CssClass = Lname.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (string.IsNullOrWhiteSpace(ConfirmPassword.Text))
            {
                flag = false;
                ConfirmPassword.CssClass = ConfirmPassword.CssClass + " redBorder";
                Message.CssClass = "alert alert-danger";
                Message.Text = "Some Fields are empty!";
            }
            if (Password.Text != ConfirmPassword.Text)
            {
                flag = false;
                Message.CssClass = "alert alert-danger";
                Message.Text = "Password does't match!";
            }
            if (flag)
            {
                int result = 0;
                int found = 1;
                found = objmyDAl.SignUp_DAL(InputFname, InputLname, InputCity, InputGender, InputPhone, InputEmail, InputPassword, ref result);
                if (found != 1)
                {
                    Message.Text = "Error connecting to server please try later";
                }
                else
                {
                    if (result == 0)
                    {
                        Message.CssClass = "alert alert-success";
                        Message.Text = "Congratulations, sign up successful!";
                        Session["user"] = InputEmail;
                        Session["type"] = 1;
                        Response.Redirect("./Home.aspx");
                    }
                    else if (result == 1)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Invalid email address provided.";
                    }
                    else if (result == 2)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "An account for this email address already exists.";
                    }
                    else if (result == 3)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Invalid phone number specified. Use 923xxxxxxxxx format.";
                    }
                    else if (result == 4)
                    {
                        Message.CssClass = "alert alert-danger";
                        Message.Text = "Invalid gender specified. Use the dropdown to select appropriate gender.";
                    }

                }
            }
        }
    }
}