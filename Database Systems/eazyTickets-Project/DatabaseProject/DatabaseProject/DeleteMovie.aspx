<%@ Page Title="" Language="C#" MasterPageFile="~/adminLayout.Master" AutoEventWireup="true" CodeBehind="DeleteMovie.aspx.cs" Inherits="DatabaseProject.DeleteMovie" %>

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

    <h1>Delete Movie</h1>

    <asp:Repeater ID="Repeater1" runat="server"
        DataSourceID="SqlDataSource1">
        <HeaderTemplate>
            <table class="table table-borderless">
                <thead>
                    <tr>
                        <th>Movie ID</th>
                        <th>Movie Name</th>
                        <th>Director</th>
                        <th>Writer</th>
                        <th>Running Time</th>
                        <th>Release Date</th>
                        <th>Genre</th>
                        <th>Main Cast</th>
                        <th>Image Link</th>
                    </tr>
                </thead>
        </HeaderTemplate>

        <ItemTemplate>
            <tbody>
                <tr>
                    <td>
                        <asp:Label CssClass="info" ID="movieId" Text='<%# Eval("movieId") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="movieName" Text='<%# Eval("movieName") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="director" Text='<%# Eval("director") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="writer" Text='<%# Eval("writer") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="runningTime" Text='<%# Eval("runningTime") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="ReleaseDate" Text='<%# Eval("ReleaseDate") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="genre" Text='<%# Eval("genre") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="mainCast" Text='<%# Eval("mainCast") %>' runat="server"></asp:Label></td>
                    <td>
                        <asp:Label CssClass="info" ID="ImageLink" Text='<%# Eval("ImageLink") %>' runat="server"></asp:Label></td>
                </tr>
            </tbody>
        </ItemTemplate>
        <FooterTemplate>
            </table>
        </FooterTemplate>
    </asp:Repeater>
    <asp:SqlDataSource ConnectionString="<%$ ConnectionStrings:sqlCon1 %>"
        ID="SqlDataSource1" runat="server"
        SelectCommand="SELECT movieId, movieName, director, writer, runningTime, ReleaseDate, genre, mainCast, ImageLink
             From [Movie]"></asp:SqlDataSource>
    <div class="container">
        <div class="row">
            <div class="center_div text-light">
                <p>Movie ID</p>
                <asp:TextBox ID="MovieID" CssClass=" form-control" runat="server" onkeypress=" valueInsert(this)" type="number"></asp:TextBox>
                <br />
                <asp:Button ID="MovieDelete" CssClass="btn btn-warning btn-block btn-lg" runat="server" Text="Delete Movie" OnClick=" DelMovie_Click" />
                <br />
                <asp:Label ID="Message" runat="server"></asp:Label>
            </div>
        </div>
    </div>

</asp:Content>

