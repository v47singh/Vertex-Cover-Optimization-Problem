# -*- coding: utf-8 -*-
"""
Created on Thu Oct  4 14:17:32 2018

@author: vaishali_singh
"""

import sys
import re
import ast

input_list = dict()

def IntersectionForOverlappingStreets(X,Y,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list):
  
  new_node="(" + str(X) + "," +str(Y) + ")"
  graph_nodes.extend(thislist)
  node_dict.append(new_node)
  nodes_intersection.append(thislist)
  graph_nodes.append(new_node)
  set_of_graph=set(graph_nodes)
  graph_nodes=list(set_of_graph)
  for t in range(0,len(graph_nodes)):
      node_list[t+1]=graph_nodes[t]


def RemoveOverlappingEdges(graph_paths, node_list, duplicate_paths):
    
    duplicate_paths1=list()
    for r in range(0,len(graph_paths)):
        path = graph_paths[r]
        path = re.sub('<', '(', path)
        path = re.sub('>', ')', path)
        path1,path2 = ast.literal_eval(path)
        if(path1==path2):
            delete="<" + str(path1) + "," + str(path2) + ">"
            duplicate_paths.append(delete)

        for i in node_list:
            node1=node_list[path1]
    
            node2=node_list[path2]
    
            nx1,ny1=ast.literal_eval(node1)
            nx2,ny2=ast.literal_eval(node2)
            nxmin = min(nx1, nx2)
            nxmax = max(nx1, nx2)
            nymin = min(ny1, ny2)
            nymax = max(ny1, ny2)
            check_path=node_list[i]

            cx,cy=ast.literal_eval(check_path)
            if((bool(cx!=nxmin) & bool( cx !=nxmax)) | ((bool(cy!=nymin) & bool(cy!=nymax)))):
                if(bool(cx <= nxmax) & bool(cx >= nxmin)):
                    if(bool(cy <= nymax) & bool(cy >= nymin)):
                        del_check="<" + str(path1) + "," + str(path2) + ">"

                        duplicate_paths.append(del_check)
                        duplicate_paths_set=set(duplicate_paths)
                        duplicate_paths=list(duplicate_paths_set)
                        
    for t in range(0,len(duplicate_paths)):
        graph_paths.remove(duplicate_paths[t])
    
    for s in range(0,len(graph_paths)):
        for v in range(s+1,len(graph_paths)):
            newpath1 = graph_paths[s]
            newpath1 = re.sub('<', '(', newpath1)
            newpath1 = re.sub('>', ')', newpath1)
            path1,path2 = ast.literal_eval(newpath1)
            newpath2 = graph_paths[v]
            newpath2 = re.sub('<', '(', newpath2)
            newpath2 = re.sub('>', ')', newpath2)
            path3,path4 = ast.literal_eval(newpath2)
            if(path1==path4 and path2==path3):
                del_chk="<" + str(path1) + "," + str(path2) + ">"
                duplicate_paths1.append(del_chk)
                duplicate_paths_set1=set(duplicate_paths1)
                duplicate_paths1=list(duplicate_paths_set1)
    

    for j in range(0,len(duplicate_paths1)):
        graph_paths.remove(duplicate_paths1[j])


def displayedges(graph_paths,graph_pathset,set_of_graph,node_list,node_dict,nodes_intersection, duplicate_paths):
            for a in range(0, len(node_dict)):
                
                point_of_intersection=node_dict[a]
                nodelist=nodes_intersection[a]
                [p1, p2, p3, p4]=nodelist
                for b in node_list:
                
                    if point_of_intersection == node_list[b]:
                        segment_intersection=b
                for i,j in node_list.items():
                    if j==p1:
                        path_p1=i
                    
                for i,j in node_list.items():
                    if j==p2:
                        path_p2=i
                    
                for i,j in node_list.items():
                     if j==p3:
                         path_p3=i
                                                                
                         for i,j in node_list.items():
                             if j==p4:
                                 path_p4=i
                       
                path1="<"+str(segment_intersection) + "," + str(path_p1) + ">"
                        
                path2="<"+str(segment_intersection) + "," + str(path_p2) + ">"
                        
                path3="<"+str(segment_intersection) + "," + str(path_p3) + ">"
                        
                path4="<"+str(segment_intersection) + "," + str(path_p4) + ">"
                        
                path_list = list((path1,path2,path3,path4))
                graph_paths.extend(path_list)
                graph_pathset=set(graph_paths)
                graph_paths=list(graph_pathset)
                distinct=list()
                for n in range(0,len(graph_paths)):
                    pair=graph_paths[n]
                    pair=re.sub('<','(',pair)
                    pair=re.sub('>',')',pair)
                    cs1,cs2 = ast.literal_eval(pair)
                    distinct.append(cs1)
                    distinct_set=set(distinct)
                    distinct=list(distinct_set)
                    for m in range(1,len(distinct)):
                        path_betweeen="<"+str(distinct[m-1]) + "," + str(distinct[m]) + ">"
                        graph_paths.append(path_betweeen)
                        set_of_graph=set(graph_paths)
                        graph_paths=list(set_of_graph)                        
           
            RemoveOverlappingEdges(graph_paths, node_list, duplicate_paths)             
            print "E ={"
            for gp in graph_paths:
                print gp
            print "}"
            

def min_vertex_cover():
    u=1;  v=1
    l=list(input_list.values())
    nodes=list(); graph_nodes=list(); graph_paths=list(); duplicate_paths=list()
    graph_pathset=set(); set_of_graph=set()
    node_dict=list(); nodes_intersection=list(); y=list()
    node_list=dict()
    
    number_of_streets=len(l)
    nodes=[None]*number_of_streets
    
    for q in range (0,number_of_streets):
        y=[i.split(', ', 1)[0] for i in l[q]]
        nodes[q]=y
    for i in range(0,number_of_streets):
        
        for j in range (i+1,number_of_streets):
             cs1 = len(nodes[i])
             
             cs2 = len(nodes[j])
             while u<cs1:
                 while v<cs2:
                      p1=nodes[i][u-1]; p2=nodes[i][u]; p3=nodes[j][v-1]; p4=nodes[j][v]
                      x1,y1 = ast.literal_eval(p1)
                      x2,y2 = ast.literal_eval(p2)
                      x3,y3 = ast.literal_eval(p3)
                      x4,y4 = ast.literal_eval(p4)
                      x1=float(x1); x2=float(x2); x3=float(x3); x4=float(x4)
                      y1=float(y1); y2=float(y2); y3=float(y3); y4=float(y4)
                      p1="(" + str(x1) + "," +str(y1) + ")"
                      p2="(" + str(x2) + "," +str(y2) + ")"
                      p3="(" + str(x3) + "," +str(y3) + ")"
                      p4="(" + str(x4) + "," +str(y4) + ")"
                      thislist = list((p1,p2,p3,p4))
                      
                      A1 = x2 - x1;    A2 = y2 - y1
                      B1 = x4 - x3;    B2 = y4 - y3
                      det = ( A1 * B2 - B1 * A2 )
                      
                      x1min = min(x1, x2); x2min = min(x3, x4); x1max = max(x1, x2); x2max = max(x3, x4)
                      y1min = min(y1, y2); y2min = min(y3, y4); y1max = max(y1, y2); y2max = max(y3, y4);
 
                      if abs(det) < 1e-20: 
                          if(p1==p4):
                            IntersectionForOverlappingStreets(x4,y4,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                            
                          elif(p2==p3):
                            IntersectionForOverlappingStreets(x3,y3,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                            
                          elif(x1==x2==x3==x4):
                            firstrangeofy=abs(y2-y1)
                            secondrangeofy=abs(y4-y3)
                            if(firstrangeofy > secondrangeofy):
                               flag=1
                               
                            elif(secondrangeofy > firstrangeofy):
                               flag=2
                               
                            if(flag == 1):
                               if(y3>y1min and y3<y1max):
                                IntersectionForOverlappingStreets(x3,y3,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                                
                               if(y4>y1min and y4<y1max):
                                IntersectionForOverlappingStreets(x4,y4,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                                
                            if(flag == 2):
                               if(y1>y2min and y1<y2max):
                                IntersectionForOverlappingStreets(x1,y1,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                                
                               if(y2>y2min and y2<y2max):
                                IntersectionForOverlappingStreets(x2,y2,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                                
                          elif(y1==y2==y3==y4):
                            firstrangeofx=abs(x2-x1)
                            secondrangeofx=abs(x4-x3)
                            if(firstrangeofx > secondrangeofx):
                                flag=1
                                
                            elif(secondrangeofx > firstrangeofx):
                                flag=2
                                
                            if(flag == 1):
                                if(x3>x1min and x3<x1max):
                                  IntersectionForOverlappingStreets(x3,y3,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                                  
                                if(x4>x1min and x4<x1max):
                                  IntersectionForOverlappingStreets(x4,y4,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                                  
                            if(flag == 2):
                                if(x1>x2min and x1<x2max):
                                  IntersectionForOverlappingStreets(x1,y1,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                                  
                                if(x2>x2min and x2<x2max):
                                  IntersectionForOverlappingStreets(x2,y2,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
         
                      else:
                         num = ( A1 * (y1 - y3) - A2 * (x1 - x3)) / det
                         denom = ( B1 * (y1 - y3) - B2 * (x1 - x3)) / det

                         if (bool(num >= 0) & bool(num <= 1) & bool(denom >= 0) & bool(denom <= 1)):
                             X=x1 + (denom * A1)
                             Y=y1 + (denom * A2)
                             
                             IntersectionForOverlappingStreets(X,Y,thislist,graph_nodes,node_dict,nodes_intersection,set_of_graph,node_list)
                         else: 
                             pass
                         
                      v=v+1
                 u=u+1
                 v=1
             u=1
                                 
             
    print "V = {"
    for x,y in node_list.items():
        print x,": ",y 
    print "}"
    displayedges(graph_paths,graph_pathset,set_of_graph,node_list,node_dict,nodes_intersection,duplicate_paths)
    
''''def input_from_user():
    street_info=sys.stdin.readline()
    return street_info.replace('\n','')'''

def CheckTheStreetName(nos):
    
    for j in input_list:
        if nos == j:
            print j
            return True
        else:
            return False
    
def do_parentheses_match(cos):
    c = []
    flag = True; i = 0
    while i < len(cos) and flag:
        chk = cos[i]
        if chk == "(":
            c.append(chk)
        elif chk == ")":
            if len(c) == 0:
                flag = False
            else:
                c.pop()

        i += 1

    return flag and len(c) == 0

def is_vertex_valid(cos):
    regex = r'\(-?\d+,-?\d+\)'
    preg = re.compile(regex)
    result= preg.match(cos)
    return result

def StreetAddition(cos,nos):
    
    if all(i.isalpha() or i.isspace() for i in nos):
        if nos in input_list:
            sys.stdout.write("Error: " + nos + " is already present and hence cannot add the street." + "\n")
        else:
            if(do_parentheses_match(cos)):
                cos=re.sub(' +','',cos)
                cos=re.sub('\)\(',') ( ',cos)
                cos=re.sub('\( ','(',cos)
                cos=cos.split(' ')
                if all(is_vertex_valid(x) for x in cos):
                    input_list[nos] = cos
                else:
                    print "Enter vertices in valid format."
            else:
               print "Paranthesis are unbalanced."
    else:
        sys.stdout.write("Error: " + "Street Name is invalid. It should contain only characters and space." + "\n")
    
def ChangesInStreet(cos,nos):
    
    if(do_parentheses_match(cos)):
            cos=re.sub(' +','',cos)
            cos=re.sub('\)\(',') ( ',cos)
            cos=re.sub('\( ','(',cos)
            cos=cos.split(' ')        
            input_list[nos] = cos
            if all(is_vertex_valid(x) for x in cos):
               input_list[nos] = cos
            else:
               print "Enter vertices in valid format."
    else:
        print "Paranthesis are unbalanced."
        
  
def RemoveTheStreet(nos):
    
    try:
        del input_list[nos]
    except KeyError:
        sys.stderr.write("Error: " + nos + " is not present and hence unable to delete." + "\n")
    
def main():
    while True:
        #street_info=input_from_user()
        street_info=raw_input()
        if(street_info ==''):
            break
        elif(street_info[0]=='r'):
            y=re.split(' +"|"|',street_info)
        else:
            y=re.split('" +| +"',street_info)
        if(len(y)==1):
            cmd=y[0]
        elif(len(y)==2):
            cmd=y[0]
            name_of_street=y[1]
            name_of_street=name_of_street.lower()   
        elif(len(y)==3):
            cmd=y[0]
            name_of_street=y[1]
            name_of_street=name_of_street.lower()
            Coordinates_of_street=y[2]
        else:
            sys.stdout.write("Error: " + "The input you have given is not valid." + "\n")
            continue
        
        if cmd == 'a':
            try:
                StreetAddition(Coordinates_of_street, name_of_street)
            except UnboundLocalError:
                sys.stderr.write("Error: " + "Please enter correct input for add command" + "\n")
            
        elif cmd == 'c':
            try:
                if name_of_street in input_list:
                    ChangesInStreet(Coordinates_of_street, name_of_street)
                else:
                    sys.stdout.write("Error: " + name_of_street + " is not present and hence unable to make changes." + "\n")
            except UnboundLocalError:
                sys.stderr.write("Error: " + "Please enter correct input for change command." + "\n")
            
        elif cmd == 'r':
            try:
                RemoveTheStreet(name_of_street)
            except UnboundLocalError:
                sys.stderr.write("Error: " + "Please enter correct input for remove command." + "\n")
            
        elif cmd == 'g':
            min_vertex_cover()
          
        else:
            sys.stdout.write("Error: " + "Please enter correct command(a,c,r,g)." + "\n")

if __name__ == '__main__':
    main()