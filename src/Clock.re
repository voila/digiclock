

[@bs.new]
external newDate: float => Js.Date.t = "Date" ;

[@bs.send]
external toString : (Js.Date.t, string) => string = "" ;

let toLocaleTimeString : (Js.Date.t, string) => string = [%bs.raw {|
  function (d, tz){
    return d.toLocaleTimeString('en-NZ', { timeZone: tz });
  }
|}
];  




/* State declaration */
type state = {
  time:float /* millisec since epoch */, 
  tz:string
};

/* Action declaration */
type action =
  | Tick
  | Time(float)
  | TimeZone(string);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Clock");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~time, ~tz, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {time, tz},
    /* State transitions */
    reducer: (action, state) =>
    switch (action) {
    | Time(t) => 
      ReasonReact.Update({...state, time:t})
    | Tick => 
      ReasonReact.Update({...state, time: state.time +. 1000.})
    | TimeZone(tz) => 
      Js.log(tz);
      ReasonReact.UpdateWithSideEffects(
      {...state, tz}, 
      (self => Tzdb.getTime(tz, t => self.send(Time(t)))))
    },
  subscriptions: (self) => [
    Sub(
      () => Js.Global.setInterval(() => {
        self.send(Tick);
      }, 1000),
      Js.Global.clearInterval
    ),

  ],
  render: self => {
    let dateString = newDate(self.state.time) |> d => toLocaleTimeString(d, self.state.tz);
    <div>
      <SelectTz cb=(tz => self.send(TimeZone(tz))) />
      <div id="digits">
        (ReasonReact.stringToElement(dateString))
      </div>
    </div>
  },
};

