<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="AddAdmin.aspx.cs" Inherits="DatabaseProject.AddAdmin" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
   <style>
        .center_div {
            display: block;
            margin: 10% auto;
            margin-top: 100px;
            width: 33%;
        }

        .redBorder {
            border-color: red;
        }


        .redText {
            color: red;
        }

        .greenText {
            color: green;
        }

        p, h1 {
            color: black;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
 <div class="container">
        <div class="row">
            <div class="center_div text-light">
                <h1>Add Admin</h1>

                <p>User ID</p>

                <asp:TextBox ID="UserIDNo" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)" type="number"></asp:TextBox>
                <br />
                <asp:Button ID="AdminSignup" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Make Admin" OnClick=" AddAdmin_Click" />
                <br />
                <asp:Label ID="Message" runat="server"></asp:Label>
            </div>

        </div>
    </div>

</asp:Content>
