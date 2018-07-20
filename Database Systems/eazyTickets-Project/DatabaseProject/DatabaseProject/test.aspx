<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="test.aspx.cs" Inherits="DatabaseProject.test" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    
    <asp:Label ID="Message" runat="server" ></asp:Label>

         <asp:repeater id="Repeater1"       
        datasourceid="easyTicketing"
        runat="server">
        
        <itemtemplate>
            <h3>User ID</h3><i><%# Eval("UserId") %></i>
            <h3>Email</h3><i><%# Eval("Email") %></i>
            <h3>Password</h3><i><%# Eval("Password") %></i>
            <asp:Button ID="Button" CssClass='<%# Eval("UserId") %>' runat="server" OnClick="MyButtonHandler" Text="Button" />           
        </itemtemplate>
          
        
      </asp:repeater>
        
            <asp:sqldatasource id="easyTicketing"          
            connectionstring="<%$ ConnectionStrings:sqlcon1%>" 
        selectcommand="SELECT UserId,Email,Password FROM [User]"
        runat="server">
      </asp:sqldatasource>
</asp:Content>
