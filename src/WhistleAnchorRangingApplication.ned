//   IPIN 2017 Localization Method Simulator
// 
//   Copyright (C) 2017 Tomasz Jankowski
//   
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 3 of the License, or
//   (at your option) any later version.
//      
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//      
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software Foundation,
//   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

package ipin2017;

//
// Application implementing anchor side of Whistle localization method.
//
simple WhistleAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(WhistleAnchorRangingApplication);
	    
	    // Whether anchor is a base node.
	    bool isBaseAnchor = default(false);
	    
	    // Delay after which anchor will transmit it's message.
	    int echoFrameDelay @unit(ps) = default(35ms);
	    
	    // File name in which measurements will be stored (do not set manually).
	    string resultsFileName = default("");
	    
}