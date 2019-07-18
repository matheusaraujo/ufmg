% This script is written and read by pdetool and should NOT be edited.
% There are two recommended alternatives:
% 1) Export the required variables from pdetool and create a MATLAB script
%    to perform operations on these.
% 2) Define the problem completely using a MATLAB script. See
%    http://www.mathworks.com/help/pde/examples/index.html for examples
%    of this approach.
function pdemodel
[pde_fig,ax]=pdeinit;
pdetool('appl_cb',9);
set(ax,'DataAspectRatio',[1 1 1]);
set(ax,'PlotBoxAspectRatio',[1.5 1 1]);
set(ax,'XLim',[-1.5 1.5]);
set(ax,'YLim',[-1 1]);
set(ax,'XTickMode','auto');
set(ax,'YTickMode','auto');

% Geometry description:
pderect([-0.5 0.5 0.5 -0.5],'Cobre');
set(findobj(get(pde_fig,'Children'),'Tag','PDEEval'),'String','Cobre')

% Boundary conditions:
pdetool('changemode',0)
pdesetbd(4,...
'dir',...
1,...
'1',...
'297')
pdesetbd(3,...
'dir',...
1,...
'1',...
'297')
pdesetbd(2,...
'dir',...
1,...
'1',...
'297')
pdesetbd(1,...
'dir',...
1,...
'1',...
'1000')

% Mesh generation:
setappdata(pde_fig,'Hgrad',1.3);
setappdata(pde_fig,'refinemethod','regular');
setappdata(pde_fig,'jiggle',char('on','mean',''));
setappdata(pde_fig,'MesherVersion','preR2013a');
pdetool('initmesh')
pdetool('refine')
pdetool('refine')

% PDE coefficients:
pdeseteq(2,...
'400',...
'0',...
'(0)+(0).*(297)',...
'(8960).*(386)',...
'0:25:1000',...
'0.0297',...
'0.0',...
'[0 100]')
setappdata(pde_fig,'currparam',...
['8960';...
'386 ';...
'400 ';...
'0   ';...
'0   ';...
'297 '])

% Solve parameters:
setappdata(pde_fig,'solveparam',...
char('0','7488','10','pdeadworst',...
'0.5','longest','0','1E-4','','fixed','Inf'))

% Plotflags and user data strings:
setappdata(pde_fig,'plotflags',[1 1 1 1 1 1 6 1 0 0 1 41 1 1 0 1 0 1]);
setappdata(pde_fig,'colstring','');
setappdata(pde_fig,'arrowstring','');
setappdata(pde_fig,'deformstring','');
setappdata(pde_fig,'heightstring','');

% Solve PDE:
pdetool('solve')
