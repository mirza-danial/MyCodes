<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="Sign_Up.aspx.cs" Inherits="DatabaseProject.Sign_Up" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
<style>
    .center_div{
    display:block;
    margin: 10% auto;
    margin-top:100px;
    width:40%;
  
}

.redBorder {
    border-color: red;
}
  

.redText{
    color:red;
}
.greenText{
    color:green;
}
p,h1{
    color:black;
}

</style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
      <div class="container">   

            <div class="row">
              
              <div class="center_div text-light" >
                  <h1>Sign up</h1>

                  <p>Name</p>
                 
                  <asp:TextBox  ID="Fname" CssClass=" form-control" Placeholder="First" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                 
                  <br/>
                  <asp:TextBox  ID="Lname" CssClass=" form-control" Placeholder="Last" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                  <br/>
                  <p>Email</p>
                  <asp:TextBox ID="Email" CssClass="form-control" Placeholder="Email" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                  <br/>
                  <p>City</p>
                   <asp:TextBox ID="City"  CssClass="form-control" runat="server"></asp:TextBox>
                  <br/>
                  <p>Mobile Number</p>
                  <asp:TextBox ID="Phone" CssClass="form-control" Placeholder="Phone" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                  <br/>
                  <p>Gender</p>
                  <asp:DropDownList ID="Gender" CssClass="btn btn-default dropdown-toggle" runat="server">
                        <asp:ListItem Text="Select" Value="0"></asp:ListItem>
                        <asp:ListItem Text="Male" Value="M"></asp:ListItem>
                        <asp:ListItem Text="Female" Value="F"></asp:ListItem>
                        <asp:ListItem Text="Other" Value="O"></asp:ListItem>

                  </asp:DropDownList>
                  <br/><br/>
                  <p>Password</p>
                  <asp:TextBox ID="Password"  CssClass="form-control" type="password" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                  <br/>
                  <p>Confirm Password</p>
                  <asp:TextBox ID="ConfirmPassword" CssClass="form-control" type="password" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                  <br/>

                  <asp:Button ID="SignUp" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Sign up" onClick=" SignUpButton_Click"/>
                  <br/>
                  <asp:Label  ID="Message" runat="server" ></asp:Label>
              </div>
             
            </div>
        </div>
        <footer class="py-5 bg-dark">
      <div class="container">
        <p class="m-0 text-center text-white">Copyright &copy; EasyTickets 2018</p>
      </div>
      <!-- /.container -->
    </footer>
   
</asp:Content>
