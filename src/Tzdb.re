let mockTimeP =
  Js.Promise.resolve(
    {|{
    "status":"OK",
    "message":"",
    "countryCode":"US",
    "countryName":"United States",
    "zoneName":"America\/Chicago",
    "abbreviation":"CST",
    "gmtOffset":-21600,
    "dst":"0",
    "dstStart":1446361200,
    "dstEnd":1457856000,
    "nextAbbreviation":"CDT",
    "timestamp":1454446991,
    "formatted":"2016-02-02 21:03:11"
    }|}
  );

exception Api_error;

let decodeTime = (json: string) : float =>
  json
  |> Json.parseOrRaise
  |> (
    json =>
      switch Json.Decode.(json |> field("status", string)) {
      | "OK" =>
        /* Current local time in Unix time */
        let timestamp = Json.Decode.(field("timestamp", float, json));
        let gmtOffset = Json.Decode.(field("gmtOffset", float, json));
        /* UTC time in Unix millisec, because Javascript */
        (timestamp -. gmtOffset) *. 1000.;
      | _ => raise(Api_error)
      }
  );

let resolveTimeP = (cb, p) : unit =>
  Js.Promise.(
    p
    |> then_(json => {
         let () = json |> decodeTime |> cb;
         resolve();
       })
    |> ignore
  );

let getTimeMock = cb => mockTimeP |> resolveTimeP(cb);

let tzdb = z => {
  let apiUrl = {j|http://api.timezonedb.com/v2/get-time-zone?key=YOUR_API_KEY&format=json&by=zone&zone=$z|j};
  Fetch.fetch(apiUrl) |> Js.Promise.then_(Fetch.Response.text);
};

let getTime = (z, cb) => tzdb(z) |> resolveTimeP(cb);