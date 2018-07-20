<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="AddCinema.aspx.cs" Inherits="DatabaseProject.AddCinema" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
 <style>
        .center_div {
            display: block;
            margin: 10% auto;
            margin-top: 100px;
            width: 33%;
        }

        .Textbox {
            min-width: 100%;
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

        .top-panel {
            border-bottom: 1px solid whitesmoke !important;
            padding-top: 100px;
            padding-bottom: 50px;
            padding-left: 100px;
        }

        .id {
            font-size: 25px !important;
            font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
        }

        .info, p {
            font-size: 15px !important;
            font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
        }

        .btn-file {
            position: relative;
            overflow: hidden;
        }

            .btn-file input[type=file] {
                position: absolute;
                top: 0;
                right: 0;
                min-width: 100%;
                min-height: 100%;
                font-size: 100px;
                text-align: right;
                filter: alpha(opacity=0);
                opacity: 0;
                outline: solid black;
                background: white;
                cursor: inherit;
                display: block;
            }

        #img-upload {
            width: 100%;
        }
    </style>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
<div class="container">
        <div class="row">
            <div class="center_div text">
                <h1>Add Cinema</h1>

                <p>Cinema Name</p>
                <asp:TextBox ID="name" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <p>Location</p>
                <asp:TextBox ID="location" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <p>Contact No</p>
                <asp:TextBox ID="phoneno" CssClass="form-control" runat="server" type="number" min="1111111111" max="9999999999" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <asp:Button ID="CinemaAdd" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Submit" OnClick="AddCinema_Click" />
                <br />
                <asp:Label ID="Message" runat="server" />
            </div>
        </div>
    </div>
</asp:Content>
