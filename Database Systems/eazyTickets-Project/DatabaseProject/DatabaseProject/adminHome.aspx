<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="adminHome.aspx.cs" Inherits="DatabaseProject.adminHome" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <style>
        .top-panel {
            border-bottom: 1px solid whitesmoke !important;
            padding-top: 100px;
            padding-bottom: 50px;
            padding-left: 100px;
        }

        .id {
            font-size: 25px !important;
            font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
            color:black !important;
        }

        .info, p {
            font-size: 15px !important;
            font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
        }

        div.a {
            text-align: center;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="top-panel">
        <span class="fa fa-user fa-5x">
            <asp:Label CssClass="id" ID="UserId" runat="server"></asp:Label>
        </span>

    </div>
    <%--<h2>Users</h2>--%>
    <asp:Repeater ID="Repeater1" runat="server"
        DataSourceID="SqlDataSource1">
        <HeaderTemplate>
            <table class="table table-borderless">
                <thead>
                    <tr>
                        <th>User ID</th>
                        <th>First Name</th>
                        <th>Last Name</th>
                        <th>Email Address</th>
                        <th>Phone Number</th>
                        <th>City</th>
                    </tr>
                </thead>
        </HeaderTemplate>

        <ItemTemplate>
            <tbody>
                <tr>
                    <td>
                        <asp:Label CssClass="info" ID="UserID" Text='<%# Eval("UserID") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="Fname" Text='<%# Eval("FirstName") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="Lname" Text='<%# Eval("LastName") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="Email" Text='<%# Eval("Email") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="Phone" Text='<%# Eval("MobileNo") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="City" Text='<%# Eval("City") %>' runat="server"></asp:Label></td>
                </tr>
            </tbody>
        </ItemTemplate>

        <FooterTemplate>
            </table>
        </FooterTemplate>
    </asp:Repeater>

    <asp:SqlDataSource ConnectionString="<%$ ConnectionStrings:sqlCon1 %>"
        ID="SqlDataSource1" runat="server"
        SelectCommand="SELECT UserID, FirstName, LastName, Email, MobileNo, City
             From [User]"></asp:SqlDataSource>

    <br />
    <div class="center_div text-light">
        <a href="/AddAdmin.aspx" class="btn btn-warning btn-block btn-lg" role="button">Add Admin</a>
        <%--<asp:Button ID="AddAdmin" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Add Admin" OnClick="location.href= './AdminSignup.aspx' " />--%>
    </div>
</asp:Content>

