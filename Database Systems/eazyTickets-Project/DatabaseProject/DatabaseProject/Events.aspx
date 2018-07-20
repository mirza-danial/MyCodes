<%@ Page Title="" Language="C#" MasterPageFile="~/Layout.Master" AutoEventWireup="true" CodeBehind="Events.aspx.cs" Inherits="DatabaseProject.Events" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
    <Script>$(document).ready(function () {
            $(".tooltip-class").hover(function () {
                $(this).attr("tooltip-data", $(this).attr("title"));
                $(this).removeAttr("title");
            }, function () {
                $(this).attr("title", $(this).attr("tooltip-data"));
                $(this).removeAttr("tooltip-data");
            });
        });</Script>
    <Style>
        .fa-cart-plus{
            color:black !important;
        }
        .form-control{
            width:60px;
        }
        .inline{
            float:left !important;
            margin-right:5px !important;
        }
        .ff{
             font-family:"Helvetica Neue", Helvetica, Arial, sans-serif;
        }
        .card-img-top{
            height:250px;
        }
      
       .ip{
            width:900px !important;
            height:350px !important;
        }
       #eventTab
       {
           background-color:#1f2833;
           color: white;
       }
       #concertTab,#movieTab{
           background-color:whitesmoke;
           color:#45a29e;
       }
        .Message
       {
           padding-bottom:20px !important;
       }
        
    </Style>
</asp:Content>

<asp:Content ID="Content4" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="container">

      <div class="row">

        <div class="col-lg-3">

          <h1 class="my-4">Eazy Tickets</h1>
          <div class="list-group">
            <a href="#" class="list-group-item" id="eventTab">Events</a>
            <a href="Concerts.aspx" class="list-group-item" id="concertTab">Concerts</a>
            <a href="Movies.aspx" class="list-group-item" id="movieTab">Movies</a>
          </div>

        </div>
        <!-- /.col-lg-3 -->
		
        <div class="col-lg-9">

          <div id="carouselExampleIndicators" class="carousel slide my-4" data-ride="carousel">
            <ol class="carousel-indicators">
              <li data-target="#carouselExampleIndicators" data-slide-to="0" class="active"></li>
              <li data-target="#carouselExampleIndicators" data-slide-to="1"></li>
              <li data-target="#carouselExampleIndicators" data-slide-to="2"></li>
            </ol>
            <div class="carousel-inner" role="listbox">
              <div class="carousel-item active">
                <img class="ip d-block img-fluid" src="images/event1.jpg" alt="First slide">
              </div>
              <div class="carousel-item">
                <img class="ip d-block img-fluid" src="images/event2.jpg" alt="Second slide">
              </div>
              <div class="carousel-item">
                <img class="d-block img-fluid ip" src="images/event3.jpg" alt="Third slide">
              </div>
            </div>
            <a class="carousel-control-prev" href="#carouselExampleIndicators" role="button" data-slide="prev">
              <span class="carousel-control-prev-icon" aria-hidden="true"></span>
              <span class="sr-only">Previous</span>
            </a>
            <a class="carousel-control-next" href="#carouselExampleIndicators" role="button" data-slide="next">
              <span class="carousel-control-next-icon" aria-hidden="true"></span>
              <span class="sr-only">Next</span>
            </a>
          </div>
        <asp:Label ID="Message" CssClass="Message" runat="server" ></asp:Label>
            <br/>
       <asp:Repeater ID="Display" runat="server">
			  <HeaderTemplate>
				<div class="row">
			  </HeaderTemplate>
					<ItemTemplate>
					<div class="col-lg-4 col-md-6 mb-4">
					  <div class="card h-100">
						<a href="#"><img class="card-img-top" src='<%# Eval("ImageLink") %>' alt=""></a>
						<div class="card-body">
						  <h4 class="card-title">
							<p ><%# Eval("eventName") %></p>
						  </h4>
						  <h5><%# Eval("cost") %> Rs</h5>
						  <p class="card-text">
                              <strong>Date: </strong><small><%# Eval("Day_Time") %></small><br/>
                              <strong>Venue: </strong><small><%# Eval("venue") %></small><br/>
                              <strong>Type: </strong><small><%# Eval("eventType") %></small><br/>
                              <strong>Organizers: </strong><small><%# Eval("organizers") %></small><br/>
						  </p>
						</div>
						<div class="card-footer">
						      <h6 class="inline">Qty:</h6> <input class=" inline form-control"  name='<%# Eval("ticketId")%>' />                 
                              
                              <asp:LinkButton CssClass="inline btn btn-info tooltip-class"  ToolTip='<%# Eval("ticketId")%>' onclick="AddToCart_Click"  ID="LinkButton1" runat="server">
                                  <span class="fa fa-cart-plus fa2x" >
                                      <small class="ff">Add to cart</small>
                                  </span>
                             </asp:LinkButton> 
						</div>
					  </div>
					</div>
				</ItemTemplate>
			  <FooterTemplate>
				</div>
			  </FooterTemplate>
          </asp:Repeater>

        </div>
        <!-- /.col-lg-9 -->

      </div>
      <!-- /.row -->

    </div>
    <!-- /.container -->
      
    <!-- Footer -->
    <footer class="py-5 bg-dark">
      <div class="container">
        <p class="m-0 text-center text-white">Copyright &copy; EasyTickets 2018</p>
      </div>
      <!-- /.container -->
    </footer>
</asp:Content>
  


