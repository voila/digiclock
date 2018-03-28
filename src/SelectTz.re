/* This is the basic component. */
let component = ReasonReact.statelessComponent("SelectTz");

[@bs.return null_to_opt] [@bs.val]
external getElementById : (string) => option(Dom.element) = "document.getElementById";

let valueOfId = id =>
switch (getElementById(id)) {
| None => ""
| Some(e) => ReactDOMRe.domElementToObj(e)##value
};


/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~cb, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: self => {
    <div>
    <select id="timezones" onChange=(_evt => cb(valueOfId("timezones")))>
        <option value="Pacific/Auckland"    > (ReasonReact.stringToElement("Pacific/Auckland")) </option>   
        <option value="Europe/Paris"        > (ReasonReact.stringToElement("Europe/Paris")) </option>         
        <option value="Europe/London"       > (ReasonReact.stringToElement("Europe/London")) </option>        
        <option value="Australia/Melbourne" > (ReasonReact.stringToElement("Australia/Melbourne")) </option>  
        <option value="Asia/Singapore"      > (ReasonReact.stringToElement("Asia/Singapore")) </option>       
        <option value="America/Los_Angeles" > (ReasonReact.stringToElement("America/Los_Angeles")) </option>  
        <option value="America/New_York"    > (ReasonReact.stringToElement("America/New_York")) </option>     
    </select>
    </div>;
  },
};
