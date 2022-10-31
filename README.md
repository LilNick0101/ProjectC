ProjectC chart editor
===============

This project has been made during the OOP course @ UniPD 2021/2022.
The purpose of this program is to create and manage charts, edit and store them using a table for
edit the graph that can be shown on the right in three different ways:  
- Bar chart  
- Cartesian graphic designer  
- Pie chart  

In this programm you can add labels and edit the chart as you wish by adding rows and columns in the editing table
editing the numeric values inside the table and change view in the chart menu.  
Finally, a chart can be saved in JSON format, a template should look like this:

     {
     "labels": [
        {
            "name": "Label name",
            "values": [
                //put as many you want
            ]
        }
    ],
    "timeline": [
        "//Strings: put as many you want"
    ],
    "title": "Chart title"
    }


