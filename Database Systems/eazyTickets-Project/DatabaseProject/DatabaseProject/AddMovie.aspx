<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="AddMovie.aspx.cs" Inherits="DatabaseProject.AddMovie" %>
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
                <h1>Add Movie</h1>

                <p>Movie Name</p>
                <asp:TextBox ID="movie" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <p>Director Name</p>
                <asp:TextBox ID="director" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <p>Writer Name</p>
                <asp:TextBox ID="writer" CssClass="form-control" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <p>Running Time</p>

                <table>
                    <tr>
                        <td><p>hh</p></td>
                        <td><p>&nbsp:&nbsp</p></td>
                        <td><p>mm</p></td>
                        <td><p>&nbsp:&nbsp</p></td>
                        <td><p>ss</p></td>
                    </tr>
                    <tr>
                        <td>
                            <asp:TextBox ID="hours" CssClass="form-control" type="number" min="1" max="12" Width="60" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox></td>
                        <td>&nbsp:&nbsp</td>
                        <td>
                            <asp:TextBox ID="minutes" CssClass="form-control" type="number" min="0" max="60" Width="60" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox></td>
                        <td>&nbsp:&nbsp</td>
                        <td>
                            <asp:TextBox ID="seconds" CssClass="form-control" type="number" min="0" max="60" Width="60" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox></td>
                    </tr>
                </table>

                <br />
                <p>Release Date</p>
                <asp:Calendar ID="RDate" runat="server" onkeypress="valueInsert(this)"></asp:Calendar>
                <br />
                <p>Genre</p>
                <asp:TextBox ID="Genre" CssClass="form-control" type="text" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <p>Main Cast</p>
                <asp:TextBox ID="Cast" CssClass="form-control" type="text" runat="server" onkeypress=" valueInsert(this)"></asp:TextBox>
                <br />
                <p>Movie Poster</p>
                <div class="input-group">
                    <span class="input-group-btn">
                        <span class="btn btn-default btn-file">Browse…
                            <asp:FileUpload ID="ImageUpload" runat="server"></asp:FileUpload>
                        </span>
                    </span>
                    <input type="text" class="form-control" readonly>
                </div>
                <br />
                <asp:Button ID="AddImage" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Submit" OnClick="AddMovie_Click" />
                <br />
                <asp:Label ID="Message" runat="server" />
            </div>
        </div>
    </div>
</asp:Content>
